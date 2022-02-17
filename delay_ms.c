/*
 * File Name: delay_ms.c
 * version: 1
 *
 * Created: 2/11/2022
 * Author: Adriana Watson
 *
 * Operations: 
 *       A simple program using the built-in clock to delay either 
 *				1ms or the users selected amount of time
 * 
 * Hardware Connection: 
 * Atmega2560          Hardware
 *           
*/
#include <avr/io.h>
void Delay_1mS(void);
void ms_Delay(uint16_t time);


void Delay_1mS(void)
{
	TCNT0 = 0;				
	TCCR0A = 0;
	TCCR0B = 0;					
	TCNT0 = 6;							//preload for a 1mSec delay
	TCCR0B = (1<<CS01) | (1<<CS00);		//CLK/64 source
	
	while((TIFR0 & (1<<TOV0))==0)		//wait for the flag to be set
	{
	}
	
	TCCR0B = 0;					//stop counting
	TIFR0 |= (1<<TOV0);			//clear the timer flag
	TCNT0 = 6;					//preload for a 1mSec delay
}

void ms_Delay(uint16_t time)
{
	uint16_t counter;
	for(counter = 0; counter < time; counter++)
	{
		Delay_1mS();
	}
}
