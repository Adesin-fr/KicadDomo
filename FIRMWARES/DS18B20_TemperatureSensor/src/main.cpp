/**
 *  DS18B20 sensor on S0 (AD1 input)
 *  DS18B20 power supply on S1 (AD0 output)
 *  Pins : PC0 /PC1

*/

#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#include <SPI.h>
#include <MySensors.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define SKETCH_NAME "DS18B20 Temp. Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define POWER_OUT			A1
#define TMP_IN			 	A0
#define PRIMARY_CHILD_ID	1
#define SLEEP_TIME 			60000	 // Sleep time between reads (in milliseconds) = 5 minutes
#define MAX_ATTACHED_DS18B20 16


MyMessage msg(PRIMARY_CHILD_ID, V_TEMP);
OneWire oneWire(TMP_IN); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass the oneWire reference to Dallas Temperature.


int lastPctBattery=0;


void before(){
	// Startup up the OneWire library
	sensors.begin();
	sensors.setResolution(12);		// 9 bit is faster than 12
}


void setup(){

	// Setup the buttons with pull-ups
	pinMode(POWER_OUT, OUTPUT);
	pinMode(TMP_IN, INPUT);
	sensors.setWaitForConversion(false);

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


float LireTemp(){
	// Fetch temperatures from Dallas sensors
	sensors.requestTemperatures();

	// query conversion time and sleep until conversion completed
	int16_t conversionTime = sensors.millisToWaitForConversion(sensors.getResolution());
	// sleep() call can be replaced by wait() call if node need to process incoming messages (or if node is repeater)
	sleep(conversionTime);

    return sensors.getTempCByIndex(0);

}

void loop() {

	float Temp;
	long VRef = VBattery();
	int pctBat 	= map(constrain(VRef, 2000, 3000), 2000, 3000, 0, 100);;

	// Power ON sensor :
	digitalWrite(POWER_OUT, HIGH);
	delay(2);	// Wait 2ms that sensor gets ready

	// Do analog conversion :
	Temp = LireTemp(),

	// Power OFF sensor, not needed anymore !
	digitalWrite(POWER_OUT, LOW);

	// Send Battery PCT if changed :
	if (lastPctBattery != pctBat){
		sendBatteryLevel(pctBat);
		lastPctBattery = pctBat;
	}

 	send(msg.set(Temp,3));

	// Sleep until key change.
	Dormir();

}
