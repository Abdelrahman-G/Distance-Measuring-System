/*
 * icu.h
 *
 *  Created on: Oct 8, 2023
 *      Author: abdel
 */

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"

/*enumeration for the clock value of timer 1*/
typedef enum {
	NO_CLOCK,CLOCK_1,CLOCK_8,CLOCK_64,CLOCK_256,CLOCK_1024
}ICU_ClockType;

/*enumeration for edge detection of timer 1*/
typedef enum{
	FALLING_EGDE,RISING_EDGE
}ICU_EgdeType;

/*Configuration types for ICU*/
typedef struct{
	ICU_ClockType clock_type;
	ICU_EgdeType edge_type;
}ICU_ConfigType;

/*
 * Description :
 * Initiate ICU in timer1 configurations
 */
void ICU_init(const ICU_ConfigType *config);

/*
 * Description :
 * Set the call back function to call when interrupt happens
 */
void ICU_setCallBack(void(*ptr)(void));

/*
 * Description :
 * Return value stored in ICR1 register
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description :
 * Set edge detection type rising edge or falling edge
 */
void ICU_setEdgeDetectionType(ICU_EgdeType edge_type);

/*
 * Description :
 * Clear timer1 counter value
 */
void ICU_clearTimerValue(void);

/*
 * Description :
 * Cancel all configurations of ICU in timer1
 */
void ICU_deInit(void);





#endif /* ICU_H_ */
