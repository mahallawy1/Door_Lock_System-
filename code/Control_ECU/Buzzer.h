/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Abdelrahman Mahalawy
 *
 ******************************************************************************/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_
#include "gpio.h"


#define BUZZER_PORT_ID     		PORTB_ID
#define BUZZER_PIN_ID       	PIN7_ID

void Buzzer_init();
void Buzzer_on();
void Buzzer_off();

#endif /* HAL_BUZZER_H_ */
