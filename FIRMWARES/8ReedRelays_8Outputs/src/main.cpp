/**
 *
 * REVISION HISTORY
 * Version 1.0 - 26/02/2017 L. Lemarinel
 *
 * DESCRIPTION
 * This sketch is used to drive 8 outputs.
 */

// Enable and select radio type attached
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#include <SPI.h>
#include <MySensors.h>

#define SN "8 Reed Relays"
#define SV "1.0"


#define NB_OUTPUTS 8
#define OUTPUT_SER		PC0	// Serial data comes on this pin
#define OUTPUT_RCLK		PC1	// This is the LATCH pin. Data is released when the pin goes HI
#define OUTPUT_SRCLK	PC2	// Clock pin

byte outputStates;


void changeOutputState(int i, boolean newState){
	bitWrite(outputStates, i, newState);

	// Lock latch
	digitalWrite(OUTPUT_RCLK, LOW);
	// Write bits
	shiftOut(OUTPUT_SER, OUTPUT_SRCLK, MSBFIRST, outputStates);
	// Unlock latch
	digitalWrite(OUTPUT_RCLK, HIGH);
}


void setup(){

	pinMode( OUTPUT_SER, OUTPUT);
	pinMode( OUTPUT_RCLK, OUTPUT);
	pinMode( OUTPUT_SRCLK, OUTPUT);

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

	// Nothing to do in the main loop !

}


void receive(const MyMessage &message){

	if (message.type == V_STATUS){
		changeOutputState(message.sensor, message.getBool());
	}

}
