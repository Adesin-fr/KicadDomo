// Enable and select radio type attached
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RF69_868MHZ

// Decommenter ceci pour activer l'affichage des "trames" dans le port série
// #define MY_DEBUG


/*
	TODO : 	implementer stockage en EEPROM du paramétrage
			Envoi des commandes directement à un noeud

*/

#include <SPI.h>
#include <MySensor.h> 

#define SN "Carte 16 Entrees"
#define SV "1.0"

#define MUX1	A0
#define MUX2	A1
#define MUXA	A2
#define MUXB	A3
#define MUXC	A4


#define SHORTPULSE 60		// Temps pour un appui court en ms
#define LONGPULSE 500		// Temps pour un appui long en ms


// La macro suivante nous donne le nombre de valeurs dans le tableau !
#define NUMBUTTONS 16

unsigned long pushTime[NUMBUTTONS];
byte pushState[NUMBUTTONS];
byte justPushed[NUMBUTTONS];
byte justReleasedShortPush[NUMBUTTONS];
byte justLongPushed[NUMBUTTONS];
byte justReleasedLongPushed[NUMBUTTONS];

#define BUTTON_STATUS_NONE 0
#define BUTTON_STATUS_PULSE_BEGIN 1
#define BUTTON_STATUS_PULSE_END 2
#define BUTTON_STATUS_HOLD_BEGIN 3
#define BUTTON_STATUS_HOLD_END 4


MySensor gw;

void setup() {
	byte i;

#ifdef MY_DEBUG
	Serial.print("Carte d'entree parametree pour ");
	Serial.print(NUMBUTTONS, DEC);
	Serial.println(" boutons ");
#endif

	// Set arrays
	for (i=0; i< NUMBUTTONS; i++) {
		pushTime[i]=0;
		justPushed[i]=0;
	}
	 
}

void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	// Paramétrer les entrées avec PULL-UP
	for (i=0; i< NUMBUTTONS; i++) {
		// Present the device :
		present(i, S_BINARY );
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

	 MyMessage msg( numpin, V_VAR1);
	 
	 
	 switch (actionType){
		 case 1:
			send(msg.set("P"));
			break;
		 case 2:
			send(msg.set("H"));
			break;
		 case 3:
			send(msg.set("R"));
			break;
	 }			 
	
}

void loop(){
	
	checkPushes();

	// Vérifier l'état de chaque broche et déclencher les evenements :
	for (int numpin=0; numpin<NUMBUTTONS; numpin++){
		if (justReleasedShortPush[numpin]==1){
			// Effacer l'evenement :
			justReleasedShortPush[numpin]=0;
			SendSensorStatus(numpin, 1);
		}

		if (justLongPushed[numpin]==1){
			// Effacer l'evenement :
			justLongPushed[numpin]=0;
			SendSensorStatus(numpin, 2);
		}

		if (justReleasedLongPushed[numpin]==1){
			// Effacer l'evenement :
			justReleasedLongPushed[numpin]=0;
			SendSensorStatus(numpin, 3);
		}
	}

	
}



boolean lirePin(byte numPin){
		
	// Définir les broches MUXA/B/C
	digitalWrite(MUXA, bitRead(ChanNumber,0));
	digitalWrite(MUXB, bitRead(ChanNumber,1));
	digitalWrite(MUXC, bitRead(ChanNumber,2));

	// Attendre un peu que le mux change de broche :
	delayMicroseconds(1);

	// Lire l'entrée
	if (numPin<8){
		return digitalRead(MUX1);
	}else{
		return digitalRead(MUX2);
	}
}
