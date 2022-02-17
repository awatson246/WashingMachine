/*
 * File Name: stepper_motor.c
 * version: 1
 *
 * Created: 1/27/2022
 * Author: Adriana Watson
 *
 * Operations: 
 *       Can rotate the motor with three different wave types given a wave input, rev input, and direction
 * 
 * Hardware Connection: 
 * Atmega2560          Hardware
*/

//include files
#include "stepper_motor.h"
#include <avr/io.h>

#include <util/delay.h>

#define STEPPER_PORT PORTF

//establish step mode arrays
uint8_t Wave[4] = {0x01, 0x02, 0x04, 0x08};
uint8_t Full[4] = {0x03, 0x06, 0x0C, 0x09};
uint8_t Half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};

//function prototypes
void stepper_io_init(void);
void stepper_Position(uint16_t degAngle, char direction);

void Stepper_Driver(char mode, uint8_t revolutions, char direction)
{
	
	uint16_t steps = 2048;								//define number of steps

	switch(mode)
	{
		case 'W':
		
		if(direction == 'R')	
		{									//wave step mode
			for(uint16_t k = 0; k < revolutions; k++)		//number of revolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(uint16_t j = 0; j < 4; j++)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Wave[j];	//push stepper values to motor
						_delay_ms(2);						//delay for speed control
					}
				}
			}
		}
		
		else if(direction == 'L')
		{
			for(uint16_t k = 0; k < revolutions; k++)		//number of revolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(int16_t j = 3; j >= 0; j--)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Wave[j];	//push stepper values to motor
						_delay_ms(2);						//delay for speed control
					}
				}
			}
		}
		break;

		case 'F':
		if(direction == 'R')							//full step mode
		{
			for(uint16_t k = 0; k < revolutions; k++)		//number of revolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(uint16_t j = 0; j < 4; j++)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Full[j];	//push stepper values to motor
						_delay_ms(6);						//delay for speed control
					}
				}
			}
		}
		
		else if(direction == 'L')
		{
			for(uint16_t k = 0; k < revolutions; k++)		//number of revolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(int16_t j = 3; j <= 0; j--)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Full[j];	//push stepper values to motor
						_delay_ms(6);						//delay for speed control
					}
				}
			}
		}
		break;

		case 'H':										//half step mode
		if(direction == 'R')
		{
			for(uint16_t k = 0; k < revolutions; k++)		//number o evolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(uint16_t j = 0; j < 8; j++)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Half[j];	//push stepper array values to motor
						_delay_ms(3);						//delay for speed control
					}
				}
			}
		}
		
		else if(direction == 'L')
		{
			for(uint16_t k = 0; k < revolutions; k++)		//number o evolutions loop
			{
				for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
				{
					for(int16_t j = 7; j >= 0; j--)			//iterate through array
					{
						STEPPER_PORT = (STEPPER_PORT & 0xF0) | Half[j];	//push stepper array values to motor
						_delay_ms(3);						//delay for speed control
					}
				}
			}
		}
		break;

	}
}

//stepper angle control
void stepper_Position(uint16_t degAngle, char direction)
{
		
	uint16_t steps = degAngle / 0.175;			//calculate number of steps needed
	
	if(direction == 'R')
	{
		for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
		{
			for(uint16_t j = 0; j < 4; j++)			//iterate through array
			{
				STEPPER_PORT = (STEPPER_PORT & 0xF0) | Wave[j];	//push array values to motor
				_delay_ms(2);						//delay for flavor
			}
		}
	}
	
	else if(direction == 'L')
	{
		for(uint16_t i = 0; i < (steps/4); i++)		//convert to sections
		{
			for(int16_t j = 3; j >= 0; j--)			//iterate through array
			{
				STEPPER_PORT = (STEPPER_PORT & 0xF0) | Wave[j];	//push array values to motor
				_delay_ms(2);						//delay for flavor
			}
		}
	}
}
