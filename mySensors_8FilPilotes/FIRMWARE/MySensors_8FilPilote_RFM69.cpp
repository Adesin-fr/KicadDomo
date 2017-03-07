/**
 *
 * REVISION HISTORY
 * Version 1.0 - 04/03/2017 L. Lemarinel
 *
 * DESCRIPTION
 * Fil pilote : 6 orders with 2 optocouplers.
 *  	each order is set with a level between 0 and 100
 *		0 to 10  : OFF
 *		11 to 20 : NO FROST
 *		21 to 30 : COMFORT - 3.5°C
 *		31 to 40 : COMFORT - 2°C
 *		41 to 50 : COMFORT - 1°C
 *		51 to 100: COMFORT

MSB FIRST :
   High Byte - Low Byte
 1  2  3  4  5  6  7  8
NP NP NP NP NP NP NP NP

 */

#define MY_DEBUG

// Enable and select radio type attached
//#define MY_RADIO_NRF24
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RF69_868MHZ


#include <SPI.h>
#include <MySensors.h>

#define SN 			"8 Fil Pilote"
#define SV 			"1.0"

#define NB_OUTS		8

#define SER_OUT		PC0
#define LAT_OUT		PC1 // RCLK
#define CLK_OUT		PC2	// SRCLK


byte currentMode[NB_OUTS];
byte currentPercent[NB_OUTS];
long nextUpdateTime[NB_OUTS];
byte nextUpdateStatus[NB_OUTS];

void setup(){

	pinMode( SER_OUT, OUTPUT);
	pinMode( LAT_OUT, OUTPUT);
	pinMode( CLK_OUT, OUTPUT);

	// Empty arrays :
	for (int i=0; i<NB_OUTS; i++){
		currentMode[i]=0;
		currentPercent[i]=0;
		nextUpdateTime[i]=0;
		nextUpdateStatus[i]=0;

		//Retreive our last state from the eprom
		currentPercent[i] = loadState(i);
	}


	applyState();

	#ifdef MY_DEBUG
		Serial.println( "Node ready to receive messages..." );
	#endif

}

void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	// Present the device :
	present(0, S_DIMMER );

}

void applyState(){

	int tempInt=0;
	byte currentMSB;
	byte currentLSB;

	for (int i=0; i<NB_OUTS; i++){
		tempInt = tempInt << 2;
		switch (currentMode[i]){
			case 1:
				tempInt |= B00000010;
				break;
			case 2:
				tempInt |= B00000001;
				break;
			case 3:
				tempInt |= B00000011;
				break;
			case 4:
				if (nextUpdateStatus[i] == 0){
					tempInt |= B00000011;
				}
				break;
			case 5:
				if (nextUpdateStatus[i] == 0){
					tempInt |= B00000011;
				}
				break;
			case 6:
				// Do nothing, we just should let it to 00 :
				// tempInt |= B00000000;
				break;
		}

	}

	currentMSB= tempInt >> 8;	// Get MSB
	currentLSB= tempInt & 0xFF; // Get LSB

	// Lock latch
	digitalWrite(LAT_OUT, LOW);
	// Write bits :
	shiftOut(SER_OUT, CLK_OUT, MSBFIRST, currentMSB);
	shiftOut(SER_OUT, CLK_OUT, MSBFIRST, currentLSB);
	// Unlock latch
	digitalWrite(LAT_OUT, HIGH);

}

void loop(){

	// check for each output to see if change is needed
	for (int i=0; i<NB_OUTS; i++){

		// Handle event type CONFORT-1 and CONFORT-2
		if (millis() >= nextUpdateTime[i] && (currentMode[i] == 4 || currentMode[i] == 5)){
			// We need to change our output status:
			if (nextUpdateStatus[i] == 1){
				// We just done 29X seconds of CONFORT, we now need to make X seconds
				if (currentMode[i] == 4){
					nextUpdateTime[i] = millis()+7000;
				}else{
					nextUpdateTime[i] = millis()+3000;
				}
				nextUpdateStatus[i] = 0;
			}else{
				if (currentMode[i] == 4){
					nextUpdateTime[i]=millis()+293000;
				}else{
					nextUpdateTime[i]=millis()+297000;
				}
				nextUpdateStatus[i]=1;
			}
			// We just changed the delays, update output :
			applyState();
		}
	}
}

void receive(const MyMessage &message){

	byte sensId = message.sensor;

	if (message.type == V_LIGHT || message.type == V_DIMMER) {
		int requestedLevel = atoi( message.data );

		#ifdef MY_DEBUG
			Serial.print( "Requested level : " );
			Serial.println( requestedLevel  );
		#endif

		requestedLevel *= ( message.type == V_LIGHT ? 100 : 1 );
		requestedLevel = requestedLevel > 100 ? 100 : requestedLevel;
		requestedLevel = requestedLevel < 0   ? 0   : requestedLevel;

		// Store current level.
		if (currentPercent[sensId] == requestedLevel){
			// Do nothing, requested level is the same that current one.
			return;
		}else{
			currentPercent[sensId] = requestedLevel;
			saveState(sensId, requestedLevel);

			if (currentPercent[sensId] <= 10){
				currentMode[sensId] = 1;
			}else if (currentPercent[sensId] > 10 and currentPercent[sensId] <= 20){
				currentMode[sensId] = 2;
			}else if (currentPercent[sensId] > 20 and currentPercent[sensId] <= 30){
				currentMode[sensId] = 3;
			}else if (currentPercent[sensId] > 30 and currentPercent[sensId] <= 40){
				// Confort - 2 : 293 + 7
				nextUpdateTime[sensId] = millis() + 293000;
				nextUpdateStatus[sensId] = 1;
				currentMode[sensId]=4;
			}else if (currentPercent[sensId] > 40 and currentPercent[sensId] <= 50){
				// Confort - 2 : 297 + 3
				nextUpdateTime[sensId] = millis() + 297000;
				nextUpdateStatus[sensId] = 1;
				currentMode[sensId] = 5;
			}else {
				// Supérieur à 51% : confort = pas de signal, 2 opto coupés
				currentMode[sensId] = 6;
			}


			applyState();
		}


	}else {
		// Do nothing
		#ifdef MY_DEBUG
	    	Serial.println( "Invalid command received..." );
		#endif

		return;
	}

}
