/**
 *
 * REVISION HISTORY
 * Version 1.0 - 24/02/2017 L. Lemarinel
 *
 * DESCRIPTION
 * This sketch is used to dim 8 Lights.
 * Each light is dimmed with a Triac.
 * Triac driving is done thru MOC3023 optocouplers
 * Each output can be controlled from the following messages :
 * 		- V_STATUS <ON/OFF> 	Toggle the light ON/OFF. If the light was previously dimmed, the previous dim level is used.
 * 		- V_PERCENTAGE <0-100> 	Set the light to the specified dim level. If the light is OFF, it will be turned ON.
 *		- V_CUSTOM 0			Triggers the default action : If the light is ON, it is switched OFF and vice-versa.
 *		- V_CUSTOM 1			Set the light ON for the amount of minutes stored in V_VAR1
 *		- V_CUSTOM 2			Begin a Dim swipe cycle : go from current dim level to 100, then go back to 0 and so on...
 *		- V_CUSTOM 3			End a dim swipe cycle : Stops on the current Dim level.
 *		- V_CUSTOM 4			Cycle thru dim values (0,2,5,10,50,100)
 *		- V_VAR1   <0-255>		Set the timer value
 *		- V_VAR2   <0-255>		Set the delay between two variations when changing dim value
 */


#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER				// Use new RFM69 Driver (include ATC)
#define MY_RFM69_FREQUENCY RFM69_868MHZ

#include <SPI.h>
#include <MySensors.h>

#define SN "Multi Dimable Light"
#define SV "1.0"


#define NB_LIGHT_OUTPUTS 8
#define OUTPUT_L0	PD1
#define OUTPUT_L1	PD0
#define OUTPUT_L2	PC5
#define OUTPUT_L3	PC4
#define OUTPUT_L4	PC3
#define OUTPUT_L5	PC2
#define OUTPUT_L6	PC1
#define OUTPUT_L7	PC0

#define EEPROM_TIMER_SETTING 1
#define EEPROM_DIMMER_DELAY 10
#define EEPROM_DIMMERTIMEOUT_VALUE 20


int CurrentLightState[NB_LIGHT_OUTPUTS];
int CurrentDimValue[NB_LIGHT_OUTPUTS];
int TargetDimValue[NB_LIGHT_OUTPUTS];
int TimerSetting[NB_LIGHT_OUTPUTS];
int TimerValue[NB_LIGHT_OUTPUTS];
int DimmerDelay[NB_LIGHT_OUTPUTS];
int SwipeCycleOn[NB_LIGHT_OUTPUTS];
unsigned long lastDimValueChangedTime[NB_LIGHT_OUTPUTS];
int DimmerTimeOut[NB_LIGHT_OUTPUTS];
byte DimmerTimeOut_DefaultValue;

void setup(){
	//Retreive our last light state from the eprom
	for (int i=0; i< NB_LIGHT_OUTPUTS; i++){
		CurrentLightState[i]= 0;
		CurrentDimValue[i]	= 0;
		TargetDimValue[i]	= 0;
		TimerValue[i]		= 0;
		SwipeCycleOn[i]		= 0;
		DimmerTimeOut[i] 		= 0;
		TimerSetting[i]		= loadState(EEPROM_TIMER_SETTING + i);
		DimmerDelay[i] 		= loadState(EEPROM_DIMMER_DELAY + i);
	}

	DimmerTimeOut_DefaultValue= loadState(EEPROM_DIMMERTIMEOUT_VALUE);

}

void presentation() {
	// Send the Sketch Version Information to the Gateway
	sendSketchInfo(SN, SV);

	// Present all the dimmers :
	for (int i=0; i< NB_LIGHT_OUTPUTS; i++){
		present(i, S_DIMMER );
	}
}

void loop(){
	for(int i=0; i<NB_LIGHT_OUTPUTS; i++){
		// Should we change the current Dimmer Values ?
		if (CurrentLightState[i]==1 && CurrentDimValue[i] != TargetDimValue[i]){
			if (lastDimValueChangedTime[i] + (DimmerDelay[i]*100) > millis()){
				lastDimValueChangedTime[i] = millis();
				// Increment or decrement the current dimmer value :
				if (CurrentDimValue[i] > TargetDimValue[i]){
					// The current value is higher than the target, we must lower it
					CurrentDimValue[i]--;
				}else{
					// The current value is lower than the target, we must increment it
					CurrentDimValue[i]++;
				}
			}
		}
		// End of IF change dimmer values

		// Are we in a swiping cycle ? If so , we should change the target value if we reach 0 or 100 :
		// TODO : We should change the DimmerDelay temporarly to be sure we have a consistent one, and restore it at the end of the swipe cycle.
		if (SwipeCycleOn[i]==1){
			if (TargetDimValue[i]==CurrentDimValue[i] && TargetDimValue[i] == 0){
				TargetDimValue[i]=100;
			}
			if (TargetDimValue[i]==CurrentDimValue[i] && TargetDimValue[i] == 100){
				TargetDimValue[i]=0;
			}
		}

	} // End of FOR loop

}

void receive(const MyMessage &message){

	int targetId = message.sensor;

	if (message.type == V_STATUS) {

		int lstate= atoi( message.data );
		if ((lstate!=0) && (lstate!=1)) {
			return;
		}else{
			// Set the new state on the output :
			CurrentLightState[targetId] = lstate;
		}
	}
	else if (message.type == V_PERCENTAGE) {
		int dimvalue= atoi( message.data );
		if ((dimvalue<0)||(dimvalue>100)) {
			// Invalid dim value
			return;
		}
		if (dimvalue==0) {
			CurrentLightState[targetId] = 0;
		}
		else {
			CurrentLightState[targetId] = 1;
			TargetDimValue[targetId]	  = dimvalue;
		}
	}
	else if (message.type == V_CUSTOM){
		int customAction = atoi( message.data );
		switch(customAction){
			case 0:
				// Toggle the light :
				if (CurrentLightState[targetId] ){
					CurrentLightState[targetId] = 0;
				}else{
					CurrentLightState[targetId] = 1;
				}
				break;
			case 1:
				// Set light ON with timer
				TimerValue[targetId] = TimerSetting[targetId];
				break;
			case 2:
				// Begin swipe cycle :
				SwipeCycleOn[targetId] = 1;
				break;
			case 3:
				// End swipe cycle :
				SwipeCycleOn[targetId] = 0;
				// TODO : restore the dimmer Delay.
				break;
			case 4:
					if (DimmerTimeOut[targetId] == 0){
						// Toggle the light :
						if (CurrentLightState[targetId] ){
							// If the light is ON , then switch it off
							CurrentLightState[targetId] = 0;
						}else{
							// if the light is OFF then switch it ON at the first level and set a timeout
							DimmerTimeOut[targetId] = DimmerTimeOut_DefaultValue;
							CurrentLightState[targetId] = 1;
							TargetDimValue[targetId] = 1;
						}
					}else{
						// Cycle thru DIM values :
						if (TargetDimValue[targetId] == 1){
							TargetDimValue[targetId] = 2;
						}else if (TargetDimValue[targetId] == 2){
							TargetDimValue[targetId] = 5;
						}else if (TargetDimValue[targetId] == 5){
							TargetDimValue[targetId] = 10;
						}else if (TargetDimValue[targetId] == 10){
							TargetDimValue[targetId] = 20;
						}else if (TargetDimValue[targetId] == 20){
							TargetDimValue[targetId] = 50;
						}else if (TargetDimValue[targetId] == 50){
							TargetDimValue[targetId] = 100;
						}
					}
					break;
		}
	}
	else if (message.type == V_VAR1){
		// Set the timer value
		int timerValue = atoi( message.data );
		// Apply the new Timer setting
		TimerSetting[targetId] = timerValue;
		// and save it to EEPROM
		saveState(EEPROM_TIMER_SETTING + targetId, timerValue);
	}
	else if (message.type == V_VAR2){
		// Set the delay between two variations when changing dim value
		int delayValue = atoi( message.data );
		// Apply the new Timer setting
		DimmerDelay[targetId] = delayValue;
		// and save it to EEPROM
		saveState(EEPROM_DIMMER_DELAY + targetId, delayValue);
	}
	else {
		// Invalid command received...
		return;
	}

}

void SendCurrentState2Controller(){
	for (int i=0; i<NB_LIGHT_OUTPUTS; i++){
		if (CurrentDimValue[i] == TargetDimValue[i]){
			MyMessage dimmerMsg(i, V_DIMMER);
			send(dimmerMsg.set(CurrentDimValue[i]));
		}
	}
}
