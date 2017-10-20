/*
* TODO : While checking for actions in main loop, store them in an array and then process them.
*			Doing the current way could lead to missed pulses ?
* Board Used : IN16_optoToMySensors ( + IN16_optocoupleurs )
*
* Description : Board with 16 inputs.
		Each input can be used as a classical button (sends a frame to gateway)
		or can send a message to another node (ie : toggle a light)
		Each input has 3 type of actions  :
			- short press
			- start of Long press
			- release of long press
Message types :
	V_VAR1 Set Target Number	(two targets are possinble : 0 or 1)
	V_VAR2 Set Destination ID
	V_VAR3 Set Child ID
	V_VAR4 Set Action Type (0 = Pulse / 1 = Hold / 2 = Release)
	V_VAR5 Set Payload Byte	(triggers EEPROM write)
	V_TEXT Get a child's configuration.

Programming is done as follow :
	i.e. to assign to input 1 target 0, node 3.8 with payload 1:
			(Input number is set via child ID of message sent.)
		Send V_VAR1 0	-- Target
		, then Send V_VAR2 3	-- Destination ID
		, then Send V_VAR3 8	-- Child ID
		, then Send V_VAR4 0	-- Action Type (0=Pulse)
		, then Send V_VAR5 1	-- Here is triggered the EEPROM write

	to reset a saved action, just set destination and child to 255.

EEPROM memory map :
	0	Input 0 /target 0 / Pulse :	Destination ID
	1								Child ID
	2								Action Payload byte
	3	Input 0 /target 0 / Hold :	Destination ID
	4								Child ID
	5								Action Payload byte
	6	Input 0 /target 0 / Relea.:	Destination ID
	7								Child ID
	8								Action Payload byte
	9	Input 0 /target 1 / Pulse :	Destination ID
	10								Child ID
	11								Action Payload byte
	12	Input 0 /target 1 / Hold :	Destination ID
	13								Child ID
	14								Action Payload byte
	15	Input 0 /target 1 / Relea.:	Destination ID
	16								Child ID
	17								Action Payload byte
	18	Input 1 /target 0 / Pulse :	Destination ID
	18	... and so on....


*/

// Enable and select radio type attached
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ
#define RFM69_ENABLE_ENCRYPTION
// La cle de cryptage doit faire exactement 16 octets
#define RFM69_ENCRYPTKEY    "Crypt_My_Home_17"

// #define MY_DEBUG



#include <Arduino.h>
#include <SPI.h>
#include <MySensors.h>

#define SKETCH_NAME "Carte 16 Entrees"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define PIN_MUX1	A0
#define PIN_MUX2	A1
#define MUXA	A2
#define MUXB	A3
#define MUXC	A4


#define SHORTPULSE 60		// Temps pour un appui court en ms
#define LONGPULSE 500		// Temps pour un appui long en ms


// La macro suivante nous donne le nombre de valeurs dans le tableau !
#define NUMBUTTONS 16
#define HEARTBEAT_DELAY 3600000


unsigned long lastHeartBeat=0;
unsigned long pushTime[NUMBUTTONS];
byte pushState[NUMBUTTONS];
byte justPushed[NUMBUTTONS];
byte justReleasedShortPush[NUMBUTTONS];
byte justLongPushed[NUMBUTTONS];
byte justReleasedLongPushed[NUMBUTTONS];

byte pgm_targetNumber;
byte pgm_destinationId;
byte pgm_childId;
byte pgm_actionType;

#define BUTTON_STATUS_NONE 0
#define BUTTON_STATUS_PULSE_BEGIN 1
#define BUTTON_STATUS_PULSE_END 2
#define BUTTON_STATUS_HOLD_BEGIN 3
#define BUTTON_STATUS_HOLD_END 4

// Function Prototypes :
boolean lirePin(byte numPin);


void setup() {
	byte i;

#ifdef MY_DEBUG
	Serial.print("Carte d'entree parametree pour ");
	Serial.print(NUMBUTTONS, DEC);
	Serial.println(" boutons ");
#endif
	// Set pins mode :
	pinMode( PIN_MUX1, INPUT_PULLUP);
	pinMode( PIN_MUX2, INPUT_PULLUP);
	pinMode( MUXA, OUTPUT);
	pinMode( MUXB, OUTPUT);
	pinMode( MUXC, OUTPUT);

	// Set arrays
	for (i=0; i< NUMBUTTONS; i++) {
		pushTime[i]=0;
		justPushed[i]=0;
	}

}

void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	for (int numpin=0; numpin<NUMBUTTONS; numpin++){
		present(numpin, S_INFO);
	}

}



void checkPushes(){
	for (int numpin=0; numpin<NUMBUTTONS; numpin++){
		if (lirePin(numpin)==LOW){
			// Si on a pas encore enregistré d'heure d'appui, on l'enregistre.
			if (pushTime[numpin]==0){
					pushTime[numpin]=millis();
			}else{
				// On vérifie depuis combien de temps le bouton est appuyé. Si plus de SHORTPULSE alors on enregistre l'appui dans le tableau :
				if (millis() >= (pushTime[numpin]+SHORTPULSE)	&& justPushed[numpin]==0 && pushState[numpin]==BUTTON_STATUS_NONE){
					#ifdef MY_DEBUG
						Serial.print("Push begin button");
						Serial.println(numpin);
					#endif
					pushState[numpin]=BUTTON_STATUS_PULSE_BEGIN;
				}
				// On a deja enregistré l'etat 1, passer au 2 ?
				if (millis() >= (pushTime[numpin]+LONGPULSE)	&& pushState[numpin]==BUTTON_STATUS_PULSE_BEGIN ){
						pushState[numpin]=BUTTON_STATUS_HOLD_BEGIN;
						justLongPushed[numpin]=1;
				}
			}
		}else{
			if (pushState[numpin]==BUTTON_STATUS_HOLD_BEGIN){
				justReleasedLongPushed[numpin]=1;
			}
			if (pushState[numpin]==BUTTON_STATUS_PULSE_BEGIN){
				#ifdef MY_DEBUG
					Serial.print("Push end button");
					Serial.println(numpin);
				#endif
				justReleasedShortPush[numpin]=1;
			}
			pushTime[numpin]=0;
			justPushed[numpin]=0;
			pushState[numpin]=BUTTON_STATUS_NONE;
		}
	}
}

void SendSensorStatus(byte numpin, byte actionType){

	MyMessage msg;
	boolean eventHandled=false;
	int eepAddress;
	byte destinationID;
	byte childID;
	byte payloadByte;


	// Check if action is set in EEPROM :
	for (int targetNumber=0; targetNumber<2; targetNumber++){
		// We check if either target 0 or 1 is set. We doesn't need 0 to be set if 1 has been set.
		eepAddress = (numpin * 18) + targetNumber * 9 + actionType * 3;
		// Check if Destination ID and Child id is set for this target (!= 255). If set, then send message.
		destinationID = loadState(eepAddress);
		childID = loadState(eepAddress+1);
		if (destinationID != 255 && childID != 255 ){
			payloadByte = loadState(eepAddress+2);
			// Prepare the message
			msg = MyMessage(0, V_CUSTOM);
			msg.setDestination(destinationID);
			msg.setSensor(childID);
			msg.set(payloadByte);
			// Send the message
			send(msg);
			eventHandled = true;
		}
	}

	if (eventHandled == false){
		msg = MyMessage(0, V_TEXT);
		switch (actionType){
			case 0:
				send(msg.set("P"));
				break;
			case 1:
				send(msg.set("H"));
				break;
			case 2:
				send(msg.set("R"));
				break;
		}
	}

}

void loop(){

	// Send a HeartBeat frequently so Domoticz see us as alive.
	if (millis() > lastHeartBeat + HEARTBEAT_DELAY){
		lastHeartBeat = millis();
		sendHeartbeat();
	}


	checkPushes();

	// Check each pin and send events :
	for (int numpin=0; numpin<NUMBUTTONS; numpin++){
		if (justReleasedShortPush[numpin]==1){
			// Clear event :
			justReleasedShortPush[numpin]=0;
			SendSensorStatus(numpin, 0);	// Handle Pulse Event type
		}

		if (justLongPushed[numpin]==1){
			// Clear event :
			justLongPushed[numpin]=0;
			SendSensorStatus(numpin, 1);	// Handle Hold Event type
		}

		if (justReleasedLongPushed[numpin]==1){
			// Clear event :
			justReleasedLongPushed[numpin]=0;
			SendSensorStatus(numpin, 2);	// Handle Release Event type
		}
	}


}


boolean lirePin(byte numPin){

	// set MUXer pins MUXA/B/C
	digitalWrite(MUXA, bitRead(numPin,0));
	digitalWrite(MUXB, bitRead(numPin,1));
	digitalWrite(MUXC, bitRead(numPin,2));

	// Wait a few microseconds for the MUXer to actually change :
	delayMicroseconds(1);

	// Lire l'entrée
	if (numPin<8){
		return digitalRead(PIN_MUX1);
	}else{
		return digitalRead(PIN_MUX2);
	}
}


void receive(const MyMessage &message){
	int byteValue;
	int inputNum;
	int eepAddress;
	MyMessage msg(0, V_TEXT);
	String tmpText="";

	inputNum=message.sensor;

	switch(message.type){
		case V_TEXT:
			// Gateway ask us to send parameters for this input...
			// Send complete parameters of targets, if set. If nothing set, send "Nothing set"
			boolean paramSet;
			byte destinationID;
			byte childID;
			byte payloadByte;
			paramSet=false;

			for (byte targetNum=0; targetNum<2; targetNum++){
				for (byte actionType=0; actionType<3; actionType++){
					eepAddress = (inputNum * 18) + targetNum * 9 + actionType * 3;
					// Check if Destination ID and Child id is set for this target (!= 255). If set, then send message.
					destinationID = loadState(eepAddress);
					childID = loadState(eepAddress+1);
					payloadByte = loadState(eepAddress+2);
					if (destinationID != 255 && childID != 255){
						// Build response :
						switch(actionType){
							case 0:
								tmpText="P/";
								break;
							case 1:
								tmpText="H/";
								break;
							case 2:
								tmpText="R/";
								break;
						}
						tmpText = tmpText + "D:" + destinationID + "." + childID + " PL:" + payloadByte;
						msg.set(tmpText);
						send(msg);
						paramSet=true;
					}
				}
			}

			if (paramSet == false){
				msg.set("Nothing Set for this input.");
				send(msg);
			}
			break;
		case V_VAR1:
			byteValue = atoi( message.data );
			// Only accept targetNumber of 0 or 1.
			if (byteValue>1) byteValue=1;
			pgm_targetNumber = byteValue;
			break;
		case V_VAR2:
			byteValue = atoi( message.data );
			pgm_destinationId = byteValue;
			break;
		case V_VAR3:
			byteValue = atoi( message.data );
			pgm_childId = byteValue;
			break;
		case V_VAR4:
			byteValue = atoi( message.data );
			// Only allow 0,1,2 action type
			if (byteValue>2) byteValue=2;
			pgm_actionType = byteValue;
			break;
		case V_VAR5:
			eepAddress = (inputNum * 18) + pgm_targetNumber * 9 + pgm_actionType * 3;
			// Get Payload value :
			byteValue = atoi( message.data );

			// Write to eeprom :
			saveState(eepAddress, pgm_destinationId);	// Save Destination ID
			saveState(eepAddress+1, pgm_childId);		// Save Child ID
			saveState(eepAddress+2, byteValue);			// Save Payload

			break;
	}


}
