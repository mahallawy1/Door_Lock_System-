/******************************************************************************
 *
 * Module: dc_motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the Motor driver
 *
 * Author: Abdelrahman Mahalawy
 *
 ******************************************************************************/


#include "gpio.h"
#include "dc_motor.h"

#include "PWM.h"
/*
 * Description:
 * DcMotor initial Fucntion
 * 1-set PIN0 and PIN1 in Port of motor to output
 * 2-Write inital value on the two pins
 */



void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN0,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN1,PIN_OUTPUT);
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN0,(MOTOR_STOP&~(1<<0)));
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN1,(MOTOR_STOP&~(1<<1)));
}


/*
 * Description:
 * DcMotor Rotate Function
 * Set the state and speed of motor
 * write State on two pins of motor
 * then set PWN in Timer0
 * input: State , unsigned char speed
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state == MOTOR_STOP)
	{
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN0,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN1,LOGIC_LOW);
	}
	else if(state == MOTOR_ANTICLOCKWISE)
	{
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN0,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN1,LOGIC_HIGH);
	}
	else if(state == MOTOR_CLOCKWISE)
	{
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN0,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN1,LOGIC_LOW);
	}
	PWM_Timer0_Start(speed);
}
