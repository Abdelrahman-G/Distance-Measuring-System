 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.c
 *
 * Description: Source file for the ICU driver
 *
 * Author: Abdelrahman gomaa
 *
 *******************************************************************************/
#include "icu.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*set uo a pointer for the call back function*/
static volatile  void (*g_callBackPtr) (void) = NULL_PTR;

/*
 * Description :
 * call the call back function when interrupt happens by ICU
 */
ISR(TIMER1_CAPT_vect){
	if (g_callBackPtr!=NULL_PTR)
		g_callBackPtr();
}

/*
 * Description :
 * Initiate ICU in timer1 configurations
 */
void ICU_init(const ICU_ConfigType *config){
	DDRD &=~(1<<PD6);
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<ICNC1);
	TCCR1B = ((TCCR1B&0xBF)) | ((config->edge_type)<<ICES1);
	TCCR1B = ((TCCR1B&0xF8)) | (config->clock_type);
	TIMSK |= (1<<TICIE1);
	TCNT1 = 0;
	ICR1 = 0;
}

/*
 * Description :
 * Set the call back function to call when interrupt happens
 */
void ICU_setCallBack(void(*ptr)(void)){
	g_callBackPtr = ptr;
}

/*
 * Description :
 * Return value stored in ICR1 register
 */
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

/*
 * Description :
 * Set edge detection type rising edge or falling edge
 */
void ICU_setEdgeDetectionType(ICU_EgdeType edge_type){
	TCCR1B = (TCCR1B&0xBF) | (edge_type<<ICES1);
}

/*
 * Description :
 * Clear timer1 counter value
 */
void ICU_clearTimerValue(void){
	TCNT1 = 0;
}

/*
 * Description :
 * Cancel all configurations of ICU in timer1
 */
void ICU_deInit(void) {
	TCNT1 = 0;
	ICR1 = 0;
	TCCR1A = 0 ;
	TCCR1B = 0;
	TIMSK&=~(1<<TICIE1);
	g_callBackPtr = NULL_PTR;
}



