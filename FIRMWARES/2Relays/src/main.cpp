/**
 *
 * REVISION HISTORY
 * Version 1.0 - 26/02/2017 L. Lemarinel
 *
 * DESCRIPTION
 * This sketch is used to drive 2 relay outputs.
 * V_STATUS set explicitly the output state
 * V_CUSTOM toggles the specified output.
*/

// Enable and select radio type attached
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#include <SPI.h>
#include <MySensors.h>

#define SN "2 Reed Relays"
#define SV "1.0"


#define NB_OUTPUTS 		2
#define OUTPUT_A		PD0	// Serial data comes on this pin
#define OUTPUT_B		PD1	// Serial data comes on this pin
#define HEARTBEAT_DELAY 3600000

byte outputStates;
unsigned long lastHeartBeat=0;


void changeOutputState(int i, boolean newState){
	bitWrite(outputStates, i, newState);

	digitalWrite(OUTPUT_A, bitRead(outputStates, 0));
	digitalWrite(OUTPUT_B, bitRead(outputStates, 1));
}



void setup(){

	pinMode( OUTPUT_A, OUTPUT);
	pinMode( OUTPUT_B, OUTPUT);

}


void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	// Present all the dimmers :
	for (int i=0; i< NB_OUTPUTS; i++){
		present(i, S_BINARY );
	}
}


void loop(){

	// Send a HeartBeat frequently so Domoticz see us as alive.
	if (millis() > lastHeartBeat + HEARTBEAT_DELAY){
		lastHeartBeat = millis();
		sendHeartbeat();
	}

}


void receive(const MyMessage &message){

	boolean currentStatus;

	switch(message.type){
		case V_CUSTOM:
			// Revert output status :
			currentStatus=bitRead(outputStates, message.sensor);
			changeOutputState(message.sensor, !currentStatus);
			break;
		case V_STATUS:
			changeOutputState(message.sensor, message.getBool());
			break;
	}


	// Send new state :
	currentStatus=bitRead(outputStates, message.sensor);
	MyMessage msg(message.sensor, V_STATUS);
	msg.set(currentStatus);
	send(msg);

}
