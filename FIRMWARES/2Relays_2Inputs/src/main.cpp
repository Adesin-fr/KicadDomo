/**
 *
 * REVISION HISTORY
 * Version 1.0 - 26/02/2017 L. Lemarinel
 *
 * Board Used : mySensors_2Relais
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

#define SN "2 Relays w. inputs"
#define SV "1.0"


#define NB_OUTPUTS 		2
#define OUTPUT_A		PD0
#define OUTPUT_B		PD1
#define INPUT_A			PD6
#define INPUT_B			PD7
#define HEARTBEAT_DELAY 3600000

byte outputStates;
boolean lastState_A;
boolean lastState_B;
unsigned long lastHeartBeat=0;


void changeOutputState(int i, boolean newState){
	bitWrite(outputStates, i, newState);

	digitalWrite(OUTPUT_A, bitRead(outputStates, 0));
	digitalWrite(OUTPUT_B, bitRead(outputStates, 1));
}



void setup(){

	pinMode( OUTPUT_A, OUTPUT);
	pinMode( OUTPUT_B, OUTPUT);

	pinMode( INPUT_A, INPUT_PULLUP);
	pinMode( INPUT_B, INPUT_PULLUP);

	lastState_A = digitalRead(INPUT_A);
	lastState_B = digitalRead(INPUT_B);

}


void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	present(0, S_BINARY );
	present(1, S_BINARY );

	present(10, S_BINARY );
	present(11, S_BINARY );


}


void loop(){

	// Send a HeartBeat frequently so Domoticz see us as alive.
	if (millis() > lastHeartBeat + HEARTBEAT_DELAY){
		lastHeartBeat = millis();
		sendHeartbeat();
	}

	if (digitalRead(INPUT_A) != lastState_A){
		delay(50);
		lastState_A = digitalRead(INPUT_A);
		MyMessage msg(10, V_STATUS);
		msg.set(lastState_A);
		send(msg);
	}

	if (digitalRead(INPUT_B) != lastState_B){
		delay(50);
		lastState_B = digitalRead(INPUT_B);
		MyMessage msg(11, V_STATUS);
		msg.set(lastState_B);
		send(msg);
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
