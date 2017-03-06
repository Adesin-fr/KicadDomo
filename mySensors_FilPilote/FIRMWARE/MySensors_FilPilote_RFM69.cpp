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
 */

#define MY_DEBUG

// Enable and select radio type attached
//#define MY_RADIO_NRF24
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RF69_868MHZ


#include <SPI.h>
#include <MySensors.h>

#define SN "Fil Pilote"
#define SV "1.0"

#define OUTPUT_P	A0	// Alternance Positive
#define OUTPUT_N	A1	// Alternance Negative

byte currentMode=0;
byte currentPercent=0;
long nextUpdateTime=0;
byte nextUpdateStatus=0;

void setup(){

	pinMode( OUTPUT_P, OUTPUT);
	pinMode( OUTPUT_N, OUTPUT);

	//Retreive our last state from the eprom
	currentPercent = loadState(1);

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

	// Disable next update for 4 and 5
	nextUpdateTime=millis()-1;
	if (currentPercent <=10){
		// Signal ARRET TOTAL = Positif seulement
		digitalWrite(OUTPUT_P, HIGH);
		digitalWrite(OUTPUT_N, LOW);
		currentMode=1;
	}else if (currentPercent >10 and currentPercent<=20){
		// Signal HORS GEL = Negatif seulement
		digitalWrite(OUTPUT_P, LOW);
		digitalWrite(OUTPUT_N, HIGH);
		currentMode=2;
	}else if (currentPercent >20 and currentPercent<=30){
		// Signal ECO : double alternance :
		digitalWrite(OUTPUT_P, HIGH);
		digitalWrite(OUTPUT_N, HIGH);
		currentMode=3;
	}else if (currentPercent >30 and currentPercent<=40){
		// Confort - 2 : 293 + 7
		digitalWrite(OUTPUT_P, LOW);
		digitalWrite(OUTPUT_N, LOW);
		nextUpdateTime=millis() + 293000;
		nextUpdateStatus = 1;
		currentMode=4;
	}else if (currentPercent >40 and currentPercent<=50){
		// Confort - 2 : 297 + 3
		digitalWrite(OUTPUT_P, LOW);
		digitalWrite(OUTPUT_N, LOW);
		nextUpdateTime=millis() + 297000;
		nextUpdateStatus = 1;
		currentMode=5;
	}else {
		// Supérieur à 51% : confort = pas de signal, 2 opto coupés
		digitalWrite(OUTPUT_P, LOW);
		digitalWrite(OUTPUT_N, LOW);
		currentMode=6;
	}
}

void loop(){

	// Handle event type CONFORT-1 and CONFORT-2
	if (millis() >= nextUpdateTime && (currentMode ==4 || currentMode==5)){
		// We need to change our output status:
		if (nextUpdateStatus==1){
			// We just done 29X seconds of CONFORT, we now need to make X seconds
			if (currentMode == 4){
				nextUpdateTime=millis()+7000;
			}else{
				nextUpdateTime=millis()+3000;
			}
			nextUpdateStatus=0;
			digitalWrite(OUTPUT_P, HIGH);
			digitalWrite(OUTPUT_N, HIGH);
		}else{
			if (currentMode == 4){
				nextUpdateTime=millis()+293000;
			}else{
				nextUpdateTime=millis()+297000;
			}
			nextUpdateStatus=1;			
			digitalWrite(OUTPUT_P, LOW);
			digitalWrite(OUTPUT_N, LOW);
		}
	}
}

void receive(const MyMessage &message){

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
		if (currentPercent == requestedLevel){
			// Do nothing, requested level is the same that current one.
			return;
		}else{
			currentPercent = requestedLevel;
			saveState(1,currentPercent);

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
