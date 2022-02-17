/*
 * File Name: stepper_motor.h
 * version: 1
 *
 * Created: 1/27/2022
 * Author: Adriana Watson
 *
 * Operations: 
 *       This is part of a mulit-module program
 * 
 * Hardware Connection: 
 * Atmega2560          Hardware
*/


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#define F_CPU 16000000UL

//include files
#include <avr/io.h>
#include <util/delay.h>

//in stepper_motor.c- drives stepper based on mode and # of revolutions
void Stepper_Driver(char mode, uint8_t revolutions, char direction);

//in stepper_motor.c- drives stepper to selected angle 
void stepper_Position(uint16_t Angle, char direction);


//#define stepper_output
extern uint8_t Wave[4];
extern uint8_t Full[4];
extern uint8_t Half[8];

#endif /* STEPPER_MOTOR_H_ */
