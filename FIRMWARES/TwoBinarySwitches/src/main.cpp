/**
 *  TODO : Handle short press / Long press / long press release (3 child per button ?)
 *		 : Handle direct actions to other node (reading config. in EEPROM)
 *	http://www.gammon.com.au/forum/?id=11497
 *  Pins : PC0 /PC1

	avrdude  -c usbasp -p m328p -U lfuse:w:0xE2:m -U hfuse:w:0xDA:m -U efuse:w:0xFF:m
*/

#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

//#define RFM69_ENABLE_ENCRYPTION
// La cle de cryptage doit faire exactement 16 octets
//#define RFM69_ENCRYPTKEY    "Crypt_My_Home_17"


#include <SPI.h>
#include <MySensors.h>

#define SKETCH_NAME "Switch Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define PRIMARY_BUTTON_PIN		A0
#define SECONDARY_BUTTON_PIN 	A1
#define PRIMARY_CHILD_ID	1
#define SECONDARY_CHILD_ID	2


MyMessage msg(PRIMARY_CHILD_ID, V_TRIPPED);
MyMessage msg2(SECONDARY_CHILD_ID, V_TRIPPED);

int sentValue=2;
int sentValue2=2;
int lastPctBattery=0;


ISR (PCINT1_vect){
	PCICR = 0;  // cancel pin change interrupts
} // end of ISR (PCINT1_vect)


void setup(){

	// Setup the buttons with pull-ups
	pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
	pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);

}

void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	// Register binary input sensor to sensor_node (they will be created as child devices)
	// You can use S_DOOR, S_MOTION or S_LIGHT here depending on your usage.
	// If S_LIGHT is used, remember to update variable type you send in. See "msg" above.
	present(PRIMARY_CHILD_ID, S_DOOR);
	present(SECONDARY_CHILD_ID, S_DOOR);
}



void Dormir(){
	set_sleep_mode (SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	byte old_ADCSRA = ADCSRA;
	// disable ADC to save power
	ADCSRA = 0;

	power_all_disable ();  // turn off various modules

	// pin change interrupt masks (see above list)
	PCMSK1 |= bit (PCINT8);		// pin PC0
	PCMSK1 |= bit (PCINT9);		// pin PC1

	PCIFR  |= bit (PCIF1);   // clear any outstanding interrupts (Need only PCIF1)
	PCICR  |= bit (PCIE1);   // enable pin change interrupts (Need only PICE1)

	// turn off brown-out enable in software
	MCUCR = bit (BODS) | bit (BODSE);
	MCUCR = bit (BODS);
	sleep_cpu ();

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



// Loop will iterate on changes on the BUTTON_PINs
void loop() {

	uint8_t value;
	long VRef = VBattery();
	int pctBat 	= map(constrain(VRef, 2000, 3000), 2000, 3000, 0, 100);;

	// Send Battery PCT if changed :
	if (lastPctBattery != pctBat){
		sendBatteryLevel(pctBat);
		lastPctBattery = pctBat;
	}

	delay(50);	// To debounce

	value = digitalRead(PRIMARY_BUTTON_PIN);

	if (value != sentValue) {
		 // Value has changed from last transmission, send the updated value
		 send(msg.set(value==HIGH ? 1 : 0));
		 sentValue = value;
	}

	value = digitalRead(SECONDARY_BUTTON_PIN);

	if (value != sentValue2) {
		 // Value has changed from last transmission, send the updated value
		 send(msg2.set(value==HIGH ? 1 : 0));
		 sentValue2 = value;
	}


	// Now we can set interrupts ON again.
	interrupts();

	// Sleep until key change.
	Dormir();

	// Be sure that we does'nt go back to interrupt when we are awake.
	noInterrupts ();

}
