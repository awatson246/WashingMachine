/*
 * version: 1
 *
 * Created: 2/11/2022
 * Author: Adriana Watson
 *
 * Operations: 
 *       Washy 
 *              washy
 * 
 * Hardware Connection: 
 * Atmega2560          Hardware
 * PORTA4:0				Switches & Pushbutton
 * PORTC2:0				LEDS
 * PORTF3:0				Stepper Motor            
*/

#include <avr/io.h>
#include "delay_ms.h"
#include "stepper_motor.h"

//inputs
#define START 0x10				//PORTA
#define DOOR 0x08				//PORT A, 0=open, 1=closed
#define TEMP_SW 0x07			//PORTA

//outputs
#define DRAIN_VALVE 0x01		//PORTC
#define HOT_WATER_VALVE 0x02	//PORTC
#define COLD_WATER_VALVE 0x04	//PORTC
#define END_CYCLE 0x08			//PORTC


void io_init(void);
char check_temp(void);
void water_control (char temp);
void stepper_agitate(uint8_t time_s);
void stepper_spin(void);


int main(void)
{
	io_init();
	
	char temp_status;
	
    while (1) 
    {
		PORTC = 0x00;
		
		while((PINA & START) == 0)
		{
			//wait for start to be pressed
		}
		
		while((PINA & DOOR) == 0)
		{
			//wait for DOOR to be closed
		}
		
		
		temp_status = check_temp();
		
		//Fill Stage
		water_control(temp_status);
		
		
		//Wash Stage
		stepper_agitate(4);				//run the motor (agitate)
		
		
		//Drain Stage
		PORTC = PORTC | DRAIN_VALVE;
		ms_Delay(4000);
		PORTC = PORTC & ~DRAIN_VALVE;
		
		//Fill Stage
		water_control(temp_status);
		
		//Rinse Stage
		stepper_agitate(6);				//run the motor (agitate)
		
		//Spin Stage
		PORTC = PORTC | DRAIN_VALVE;
									//run the motor (High Speed CW)
		stepper_spin();
		PORTC = PORTC & ~DRAIN_VALVE;
		
		//The End
		PORTC = PORTC | END_CYCLE;			//cycle end indicator
		ms_Delay(5000);
		PORTC = 0x00;
	}
}

void io_init(void)
{
	//Switches & Pushbutton
	DDRA = 0x00;    //Port A set as input
	PORTA = 0xFF;   //turn off LED at init
	
	//LEDs
	DDRC = 0xFF;	//Port C initialized for outputs
	PORTC = 0x00;	//Pull-up resistors
	
	//Stepper motor
	DDRF = 0xFF;    //Port F set as output
	PORTF = 0x00;   //turn off LED at init
}

char check_temp(void)
{
	while(TEMP_SW==0)
	{
		//wait for temp to be selected
	}
	
	if((PINA & TEMP_SW) == 0x01)
	{
		return 'H';
	}
	
	else if ((PINA & TEMP_SW) == 0x02)
	{
		return 'W';
	}
	
	else if((PINA & TEMP_SW) == 0x04)
	{
		return 'C';
	}
}

void water_control (char temp)
{
	switch (temp)
	{
		case 'H':
			PORTC = PORTC | HOT_WATER_VALVE;
			ms_Delay(4000);
			PORTC = PORTC & ~HOT_WATER_VALVE;
			break;
		case 'W':
			PORTC = PORTC | HOT_WATER_VALVE | COLD_WATER_VALVE;
			ms_Delay(4000);
			PORTC = PORTC & ~HOT_WATER_VALVE & ~COLD_WATER_VALVE;
			break;
		case 'C':
			PORTC = PORTC | COLD_WATER_VALVE;
			ms_Delay(4000);
			PORTC = PORTC & ~COLD_WATER_VALVE;
			break;	
	}
}

void stepper_agitate(uint8_t time_s)
{
	time_s = time_s/2;
	
	for(uint8_t ctr = 1; ctr <= time_s; ctr++)
	{
		stepper_Position(90, 'R');
		stepper_Position(90, 'L');
	}

}

void stepper_spin(void)
{
	Stepper_Driver('W', 2, 'R');
}
