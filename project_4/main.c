 /******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Source file for the the program
 *
 * Author: Abdelrahman gomaa
 *
 *******************************************************************************/
#include "std_types.h"
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>
#define DISTANCE_DISPLAY_COL 11
#define DISTANCE_DISPLAY_ROW 0

/*
 * Description:
 * modifies the number written on LCD.
*/
void DisplayOnLCD(const uint16 *distance){
	if (*distance<10){
		LCD_displayStringRowColumn(DISTANCE_DISPLAY_ROW, DISTANCE_DISPLAY_COL+1, "  ");
	}
	else if (*distance<100)
		LCD_displayStringRowColumn(DISTANCE_DISPLAY_ROW, DISTANCE_DISPLAY_COL+2, " ");
}


int main(void) {
	/*set the I-bit because the interrupt is used in ICU*/
	SREG|=(1<<7);

	LCD_init();
	Ultrasonic_init();
	/*Send the Trigger pulse to the Ultrasonic to start the ranging*/
	Ultrasonic_Trigger();
	LCD_displayString("distance = ");
	LCD_displayStringRowColumn(DISTANCE_DISPLAY_ROW, DISTANCE_DISPLAY_COL+3, "cm");

	while(1){
		LCD_moveCursor(DISTANCE_DISPLAY_ROW, DISTANCE_DISPLAY_COL);
		uint16 distance = Ultrasonic_readDistance();
		LCD_intgerToString(distance);
		DisplayOnLCD(&distance);
	}
}

