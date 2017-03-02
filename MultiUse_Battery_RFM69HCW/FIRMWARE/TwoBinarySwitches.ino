/**
 *  TODO : Handle short press / Long press / long press release (3 child per button ?)
 *		 : Handle direct actions to other node (reading config. in EEPROM)
 *	http://www.gammon.com.au/forum/?id=11497
 *  Pins : PC0 /PC1


	Pin change interrupts.

	Pin                  Mask / Flag / Enable

	D0	  PCINT16 (PCMSK2 / PCIF2 / PCIE2)
	D1	  PCINT17 (PCMSK2 / PCIF2 / PCIE2)
	D2	  PCINT18 (PCMSK2 / PCIF2 / PCIE2)
	D3	  PCINT19 (PCMSK2 / PCIF2 / PCIE2)
	D4	  PCINT20 (PCMSK2 / PCIF2 / PCIE2)
	D5	  PCINT21 (PCMSK2 / PCIF2 / PCIE2)
	D6	  PCINT22 (PCMSK2 / PCIF2 / PCIE2)
	D7	  PCINT23 (PCMSK2 / PCIF2 / PCIE2)
	D8	  PCINT0 (PCMSK0 / PCIF0 / PCIE0)
	D9	  PCINT1 (PCMSK0 / PCIF0 / PCIE0)
	D10	  PCINT2 (PCMSK0 / PCIF0 / PCIE0)
	D11	  PCINT3 (PCMSK0 / PCIF0 / PCIE0)
	D12	  PCINT4 (PCMSK0 / PCIF0 / PCIE0)
	D13	  PCINT5 (PCMSK0 / PCIF0 / PCIE0)
	A0	  PCINT8 (PCMSK1 / PCIF1 / PCIE1)
	A1	  PCINT9 (PCMSK1 / PCIF1 / PCIE1)
	A2	  PCINT10 (PCMSK1 / PCIF1 / PCIE1)
	A3	  PCINT11 (PCMSK1 / PCIF1 / PCIE1)
	A4	  PCINT12 (PCMSK1 / PCIF1 / PCIE1)
	A5	  PCINT13 (PCMSK1 / PCIF1 / PCIE1)
*/

#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RF69_868MHZ

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

	// pin change interrupt masks (see above list)
	PCMSK1 |= bit (PCINT8);		// pin PC0
	PCMSK1 |= bit (PCINT9);		// pin PC1

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

	PCIFR  |= bit bit (PCIF1);   // clear any outstanding interrupts (Need only PCIF1)
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


int PctBattery(){
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

	return map(constrain(tension_alim,2,3), 2, 3, 0, 100);
}

// Loop will iterate on changes on the BUTTON_PINs
void loop() {

	uint8_t value;
	int pctBat;

	// Sleep until key change.
	Dormir();

	// Be sure that we does'nt go back to interrupt when we are awake.
	noInterrupts ();

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

	pctBat = PctBattery();
	// Send Voltage :
	if (lastPctBattery != pctBat){
		sendBatteryLevel(pctBat);
		lastPctBattery = pctBat;
	}
	// Now we can set interrupts ON again.
	interrupts();

}