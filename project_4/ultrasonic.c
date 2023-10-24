/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Source file for the Ultrasonic driver
 *
 * Author: Abdelrahman gomaa
 *
 *******************************************************************************/
#include "ultrasonic.h"
uint16 g_timerValue = 0;
uint8 edge_triggers = 0;

/*
 * Description :
 * set up trigger pin direction of the Ultrasonic Ranging module.
 * set the configurations of the ICU with clock = F_CPU/8.
 * detect the raising edge as the first edge.
 * set the call back function of the ICU to the edge Processing function of the module
 */
void Ultrasonic_init(void) {

	GPIO_setupPinDirection(MODULE_TRIGGER_PORT, MODULE_TRIGGER_PIN, PIN_OUTPUT);
	GPIO_writePin(MODULE_TRIGGER_PORT, MODULE_TRIGGER_PIN, LOGIC_LOW);

	ICU_ConfigType config_type = { CLOCK_8, RISING_EDGE };
	ICU_init(&config_type);

	ICU_setCallBack(Ultrasonic_edgeProcessing);
}

/*
 * Description :
 * Send the Trigger pulse to the Ultrasonic and delay for 10us
 */
void Ultrasonic_Trigger(void) {
	GPIO_writePin(MODULE_TRIGGER_PORT, MODULE_TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(TRIGGER_TIME_DELAY);
	GPIO_writePin(MODULE_TRIGGER_PORT, MODULE_TRIGGER_PIN, LOGIC_LOW);

}

/*
 * Description :
 * Calls Ultrasonic Trigger function to start ranging.
 * The function waits for the echo signal to return (falling edge detection),
 * then it calculates the distance:
 * 			distance = speed * time
 * 			speed = 34000 cm/s
 * 			time = time of high (ECHO) pulse / 2
 * 			distance = (34000 * timer value * 10^-6(time in us)) / 2
 * 			distance = timer value * 58.8
 */
uint16 Ultrasonic_readDistance(void) {
	/* Send the trigger pulse using Ultrasonic_Trigger function.*/
	Ultrasonic_Trigger();
	while (edge_triggers != 2)
		;
	edge_triggers = 0;
	uint16 distance = (float) (g_timerValue / 58) + 1;
	return distance;
}

/*
 *  This is the call back function.
 *  edge triggers variable indicates whether it is a rising or falling edge is detected.
 *  if edge triggers is 1 then this is a rising edge and the timer should start counting.
 *  if edge triggers is 2 then this is a falling edge and the timer value should be stored.
 *  make the ICU detect rising edges again for further detections.
 */
void Ultrasonic_edgeProcessing(void) {
	edge_triggers++;
	if (edge_triggers == 1) {
		/*clear timer value to start counting the time for pulse width*/
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING_EGDE);
	} else if (edge_triggers == 2) {
		/*store the value of the timer to calculate the distance*/
		g_timerValue = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RISING_EDGE);
	}
}

