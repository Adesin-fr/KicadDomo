/**
 *
 * REVISION HISTORY
 * Version 1.0 - 26/02/2017 L. Lemarinel
 *
 * DESCRIPTION
 * This sketch is used to drive 4 blinds.
 * Each blind is moved using 2 relays.
 * A relay can set an UP or DOWN movement. So, each blind needs 2 relays.
 * Relays are drove using a 74HC595 shifter.
 * Each bline can be controlled from the following messages :
 * 		- V_UP					Set the blind all way up/opened
 * 		- V_DOWN				Set the blind all way down/closed
 * 		- V_STOP				Stop the blinds to its actual position when moving.
 * 		- V_PERCENTAGE <0-100> 	Set the blind to the following position, according to calibration delay
 * 		- V_CUSTOM				Cycle thru following actions : UP/STOP/DOWN/STOP/UP/...
 *		- V_VAR1   <0-255>		Set the calibration delay for the blind
 */


// Enable debug prints
#define MY_DEBUG

// Enable and select radio type attached
//#define MY_RADIO_NRF24
#define MY_RADIO_RFM69

#include <SPI.h>
#include <MySensors.h>

#define SN "4 Blinds"
#define SV "1.0"


#define NB_BLINDS 4
#define OUTPUT_SER		PC0	// Serial data comes on this pin
#define OUTPUT_RCLK		PC1	// This is the LATCH pin. Data is released when the pin goes HI
#define OUTPUT_SRCLK	PC2	// Clock pin

#define EEPROM_CALIB_DELAY 1


enum blindMovement{ movingUp, movingDown, movingUnknown};

int CurrentBlindPos[NB_BLINDS];				// Current position in percent
int TargetBlindPos[NB_BLINDS];				// Target position in percent
blindMovement LastBlindMovement[NB_BLINDS];	// Last movement (used for ACTION messages)
boolean BlindIsMoving[NB_BLINDS];			// Is blind moving ? 
long BlindStartMoveTime[NB_BLINDS];			// start moving time of blind, according to millis()
int neededMoveTime[NB_BLINDS];				// time needed for complete operation.
int BlindCalibDelay[NB_BLINDS];				// time needed for complete operation.
long lastRefreshTime = 0;
byte outputStates = 0;


void WriteOutputStates(){
	digitalWrite(OUTPUT_RCLK, LOW);
	shiftOut(OUTPUT_SER, OUTPUT_SRCLK, MSBFIRST, outputStates);
	digitalWrite(OUTPUT_RCLK, HIGH);
}

void StopBlind(int i){
	// STOPS the [i] blind.
	TargetBlindPos[i]=CurrentBlindPos[i];
	bitWrite(outputStates, 2*i, 0);
	bitWrite(outputStates, 2*i + 1, 0);
}

void SetNewPos(int i, int pos){
	// Sets the [i] blind to [pos] percent.

	// Do not set invalid positions ! 	
	if (pos>100 && pos <0){
		return;
	}

	if (pos > CurrentBlindPos[i]){
		// Need to move UP
		bitWrite(outputStates, 2*i, 1);
		bitWrite(outputStates, 2*i + 1, 0);
		neededMoveTime[i]	= pos - CurrentBlindPos[i] * BlindCalibDelay[i] / 100;

	}else if (pos < CurrentBlindPos[i]){
		// Need to move DOWN
		bitWrite(outputStates, 2*i, 0);
		bitWrite(outputStates, 2*i + 1, 1);
		neededMoveTime[i]	=  CurrentBlindPos[i] - pos * BlindCalibDelay[i] / 100;

	}else{
		// Position is same that previous set. Do nothing.
		return;
	}
	BlindIsMoving[i]	= true;
	TargetBlindPos[i]	= pos;
	BlindStartMoveTime	= millis();
}


void setup(){
	//Retreive our last light state from the eprom
	for (int i=0; i< NB_BLINDS; i++){
		CurrentBlindPos[i]		= 0;
		TargetBlindPos[i]		= 0;
		LastBlindMovement[i]	= movingUnknown;
		BlindIsMoving[i]		= false;
		BlindStartMoveTime[i]	= 0;
		BlindCalibDelay[i] 		= loadState(EEPROM_CALIB_DELAY + i);
	}

	pinMode( OUTPUT_SER, OUTPUT);
	pinMode( OUTPUT_RCLK, OUTPUT);
	pinMode( OUTPUT_SRCLK, OUTPUT);

	#ifdef MY_DEBUG
		Serial.println( "Node ready to receive messages..." );
	#endif
}

void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	// Present all the dimmers :
	for (int i=0; i< NB_BLINDS; i++){
		present(i, S_COVER );
	}
}

void loop(){

	// Wait 1 second between each check.
	if (millis() > lastRefreshTime+1000){
		
		lastRefreshTime = millis();

		for(int i=0; i<NB_BLINDS; i++){
			// Should we stop the blind ?
			if (CurrentBlindPos[i] != TargetBlindPos[i]  ){
				// Get the current position (time since movement start VS total time needed)
				CurrentBlindPos[i] = (millis() - BlindStartMoveTime[i])*100/neededMoveTime[i];

				if (CurrentBlindPos[i] == TargetBlindPos[i]){
					StopBlind(i);
				}
				// Send current blind position update :
				SendBlindPosition(i);
			}

		} // End of FOR loop

	}

}

void receive(const MyMessage &message){

	if (message.type == V_UP) {
		#ifdef MY_DEBUG
			Serial.println( "V_UP command received..." );
		#endif

		// Set the new position :
		SetNewPos([message.sensor], 100);

	}
	else if (message.type == V_DOWN) {
		#ifdef MY_DEBUG
			Serial.println( "V_DOWN command received..." );
		#endif

		// Set the new position :
		SetNewPos([message.sensor], 0);
	}
	else if (message.type == V_PERCENTAGE) {

		int pctValue = atoi( message.data );
		
		if ((pctValue<0)||(pctValue>100)) {
			// Invalid pct  value
			#ifdef MY_DEBUG
				Serial.println( "Invalid V_PERCENTAGE data received (should be 0-100)" );
			#endif
			return;
		}

		SetNewPos([message.sensor], pctValue);

	}
	else if (message.type == V_CUSTOM){
		// If blind is moving, stop it. Otherwise, if it was going down before being stopped, pull it up, else down.
		if (BlindIsMoving[message.sensor]){
			StopBlind[message.sensor];
		}else{
			if (LastBlindMovement[message.sensor]==movingDown){
				SetNewPos([message.sensor],100);
			}else{
				SetNewPos([message.sensor],0);				
			}
		}
	}
	else if (message.type == V_VAR1){
		// Set the delay value
		int timerValue = atoi( message.data );
		// Apply the new Timer setting
		BlindCalibDelay[message.sensor] = timerValue;
		// and save it to EEPROM
		saveState(EEPROM_CALIB_DELAY + i, timerValue);
	}
	else {
		#ifdef MY_DEBUG
	    	Serial.println( "Invalid command received..." );
		#endif

		return;
	}

}

void SendBlindPosition(int i){
	MyMessage blindMsg(i, V_PERCENTAGE);
	send(blindMsg.set(CurrentBlindPos[i]));
}
