/**
 *  LMT85 sensor on S0 (AD1 input)
 *  LMT85 power supply on S1 (AD0 output)
 *  Pins : PC0 /PC1

	// LMT85
	//Temp = ((lectureMV) - 1569) / -8.2;
	// LMT86 :
	 Temp = ((lectureMV) - 2103) / -10.9;
*/

#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#include <SPI.h>
#include <MySensors.h>

#define SKETCH_NAME "LMT85 Temp. Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define POWER_OUT			A1
#define TMP_IN			 	A0
#define PRIMARY_CHILD_ID	1
#define SLEEP_TIME 			300000	 // Sleep time between reads (in milliseconds) = 5 minutes
#define NB_READ_AVERAGE		3		 // Make X readings and make an average

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


long VBattery(){
	/* Elimine toutes charges résiduelles */
	ADMUX = (_BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) );
	delayMicroseconds(350);

	/* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
	ADMUX = 0x4E;
	delayMicroseconds(200);

	/* Active le convertisseur analogique -> numérique */
	ADCSRA |= _BV(ADSC);

	/* Attend la fin de la conversion */
	while(bit_is_set(ADCSRA, ADSC));

	/* Récupère le résultat de la conversion */
	long vcc = 1125300L / ADC;

	return vcc;
}

float ReadTemp(long VRef){
	float Temp;
	long value;
	for(int i=0; i<NB_READ_AVERAGE; i++){
		// Do analog conversion :
		value = analogRead(TMP_IN);
		long lectureMV = (value * VRef) / 1023;

		// LMT85
		//Temp = ((lectureMV) - 1569) / -8.2;
		// LMT86 :
		Temp += ((lectureMV) - 2103) / -10.9;
	}
	return( Temp / NB_READ_AVERAGE );
}

// Loop will iterate on changes on the BUTTON_PINs
void loop() {
	float Temp;
	long VRef;
	int pctBat;

	// Power ON sensor :
	digitalWrite(POWER_OUT, HIGH);

	// Wait 2ms that battery settles :
	delay(2);

	VRef = VBattery();
	pctBat 	= map(constrain(VRef, 2000, 3000), 2000, 3000, 0, 100);;

	// Tension de reference = AVCC
	ADMUX |= (1 >> REFS0);

	Temp = ReadTemp(VRef);

	// Power OFF sensor, not needed anymore !
	digitalWrite(POWER_OUT, LOW);

	// Send Battery PCT if changed :
	if (lastPctBattery != pctBat){
		sendBatteryLevel(pctBat);
		lastPctBattery = pctBat;
	}

 	send(msg.set(Temp,2));

	// Sleep until next measure.
	Dormir();

}
