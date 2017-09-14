#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#define RFM69_ENABLE_ENCRYPTION
// La cle de cryptage doit faire exactement 16 octets
#define RFM69_ENCRYPTKEY    "Crypt_My_Home_17"

#define MY_DEFAULT_TX_LED_PIN  4  // the PCB, on board LED
#define MY_DEFAULT_RX_LED_PIN  5  // Receive led pin
#define MY_DEFAULT_ERR_LED_PIN 6  // Error led pin

// Enable serial gateway
#define MY_GATEWAY_SERIAL

// Disable splash screen : causes problems with openHab binding
#define MY_SPLASH_SCREEN_DISABLED

#include <MySensors.h>


void setup(){
}

void presentation() {
}

void loop() {
}
