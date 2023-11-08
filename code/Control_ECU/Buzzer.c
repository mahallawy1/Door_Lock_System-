/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Abdelrahman Mahalawy
 *
 ******************************************************************************/
#include "Buzzer.h"
#include "std_types.h"

void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_LOW);
}
void Buzzer_on()
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_HIGH);
}
void Buzzer_off()
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_LOW);
}
