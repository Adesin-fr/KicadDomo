#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#define RFM69_ENABLE_ENCRYPTION
#define RFM69_ENCRYPTKEY    "Crypt_My_Home_17"


#include <SPI.h>
#include <MySensors.h>

#define SKETCH_NAME "FS300A Water counter"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"


#define PRIMARY_COUNT_PIN		A0
#define PRIMARY_CHILD_ID	1
#define SECONDARY_CHILD_ID	2


MyMessage msgPrimary(PRIMARY_CHILD_ID, V_VOLUME);
MyMessage msgSecondary(SECONDARY_CHILD_ID, V_VOLUME);


#define PULSE_PER_LITRE 10		// My FS300A is given for 330 pulse/litre. Some says 5500/m3 !?
unsigned long pulseCounter=0;
unsigned long volumeCounter=0;
unsigned long lastVolumeSent=0;
int lastPctBattery=0;


ISR (PCINT1_vect){
	PCICR = 0;  // cancel pin change interrupts
	pulseCounter++;

} // end of ISR (PCINT1_vect)


void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	// Register binary input sensor to sensor_node (they will be created as child devices)
	// You can use S_DOOR, S_MOTION or S_LIGHT here depending on your usage.
	// If S_LIGHT is used, remember to update variable type you send in. See "msg" above.
	present(PRIMARY_CHILD_ID, S_WATER);
	present(SECONDARY_CHILD_ID, S_WATER);
}


void Dormir(){

	// Now we can set interrupts ON again.
	interrupts();

	set_sleep_mode (SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	byte old_ADCSRA = ADCSRA;
	// disable ADC to save power
	ADCSRA = 0;

	power_all_disable ();  // turn off various modules


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

	// Be sure that we does'nt go back to interrupt when we are awake.
	noInterrupts ();

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


void setup() {
    // put your setup code here, to run once:
	pinMode(PRIMARY_COUNT_PIN, INPUT_PULLUP);

	// pin change interrupt masks
	PCMSK1 |= bit (PCINT8);		// pin PC0
	PCMSK1 |= bit (PCINT9);		// pin PC1

}


void loop() {

	while (pulseCounter>=PULSE_PER_LITRE){
		volumeCounter++;
		pulseCounter -= PULSE_PER_LITRE;
	}

	if (volumeCounter!=lastVolumeSent ){


		long VRef = VBattery();
		int pctBat 	= map(constrain(VRef, 2000, 3000), 2000, 3000, 0, 100);;

		// Send Battery PCT if changed :
		if (lastPctBattery != pctBat){
			sendBatteryLevel(pctBat);
			lastPctBattery = pctBat;
		}

		// Send pulse counter and reset it .
		send( msgPrimary.set(volumeCounter) );

		lastVolumeSent=volumeCounter;
	}

	// Sleep until next pulse
	Dormir();


}
