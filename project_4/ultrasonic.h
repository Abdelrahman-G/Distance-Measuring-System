/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Header file for the Ultrasonic driver
 *
 * Author: Abdelrahman gomaa
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"
#include "icu.h"
#include "GPIO.h"
#include "lcd.h"
#include <util/delay.h>
#include <avr/io.h>

#define MODULE_TRIGGER_PORT PORTB_ID
#define MODULE_TRIGGER_PIN PIN5_ID
#define TRIGGER_TIME_DELAY 10

/*
 * Description :
 * set up trigger pin direction of the Ultrasonic Ranging module.
 * set the configurations of the ICU with clock = F_CPU/8.
 * detect the raising edge as the first edge.
 * set the call back function of the ICU to the edge Processing function of the module
 */
void Ultrasonic_init(void);

/*
 * Description :
 * Send the Trigger pulse to the Ultrasonic and delay for 10us
 */
void Ultrasonic_Trigger(void);

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
uint16 Ultrasonic_readDistance(void);

/*
 *  This is the call back function.
 *  edge triggers variable indicates whether it is a rising or falling edge is detected.
 *  if edge triggers is 1 then this is a rising edge and the timer should start counting.
 *  if edge triggers is 2 then this is a falling edge and the timer value should be stored.
 *  make the ICU detect rising edges again for further detections.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
