/**
 *  LMT85 sensor on S0 (AD1 input)
 *  LMT85 power supply on S1 (AD0 output)
 *	http://www.gammon.com.au/forum/?id=11497
 *  Pins : PC0 /PC1

	LMT85 : Temp = ((lecture mv) - 1569) / -8.2

*/

#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RF69_868MHZ

#include <SPI.h>
#include <MySensors.h>

#define SKETCH_NAME "TMP35 Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define POWER_OUT			A0
#define TMP_IN			 	A1
#define PRIMARY_CHILD_ID	1
#define SLEEP_TIME 			300000	 // Sleep time between reads (in milliseconds) = 5 minutes


MyMessage msg(PRIMARY_CHILD_ID, V_TEMP);

int lastPctBattery=0;


void setup(){

	// Setup the buttons with pull-ups
	pinMode(POWER_OUT, OUTPUT);
	pinMode(TMP_IN, INPUT);

}

void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	present(PRIMARY_CHILD_ID, S_TEMP);
}



void Dormir(){

	byte old_ADCSRA = ADCSRA;
	// disable ADC to save power
	ADCSRA = 0;


	sleep(SLEEP_TIME);


	// cancel sleep as a precaution
	sleep_disable();
	power_all_enable ();   // enable modules again
	ADCSRA = old_ADCSRA;   // re-enable ADC conversion
}


float VBattery(){
	/* Elimine toutes charges résiduelles */
	ADMUX = 0x4F;
	delayMicroseconds(5);

	/* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
	ADMUX = 0x4E;
	delayMicroseconds(200);

	/* Active le convertisseur analogique -> numérique */
	ADCSRA |= (1 << ADEN);

	/* Lance une conversion analogique -> numérique */
	ADCSRA |= (1 << ADSC);

	/* Attend la fin de la conversion */
	while(ADCSRA & (1 << ADSC));

	/* Récupère le résultat de la conversion */
	float tension_alim = (1023 * 1.1) / (ADCL | (ADCH << 8));

}

// Loop will iterate on changes on the BUTTON_PINs
void loop() {

	long Temp;
	float VRef = VBattery();
	int pctBat 	= map(constrain(VRef,2,3), 2, 3, 0, 100);;

	// Send Battery PCT if changed :
	if (lastPctBattery != pctBat){
		sendBatteryLevel(pctBat);
		lastPctBattery = pctBat;
	}

	// Power ON sensor :
	digitalWrite(POWER_OUT, HIGH);
	delay(2);	// Wait 2ms that sensor gets ready

	// Do analog conversion :
	value = analogRead(TMP_IN);

	// Power OFF sensor, not needed anymore !
	digitalWrite(POWER_OUT, LOW);


	float lectureMV = value * VRef /1023;

	Temp = ((lectureMV) - 1569) / -8.2;

 	send(msg.set(Temp,1));


	// Sleep until key change.
	Dormir();

}