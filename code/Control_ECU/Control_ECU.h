/*
 * Control_ECU.h
 *
 *  Created on: 3 Nov 2023
 *      Author: Abdelrahman Mahalawy
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_
//INCLUDES
#include "dc_motor.h"
#include "avr/io.h"
#include "timer.h"
#include "Buzzer.h"
#include "twi.h"
#include "std_types.h"
#include <util/delay.h>
#include "uart.h"
#include "external_eeprom.h"

//#DEFINES

#define REG_PASSWORD 0x10			// Asking For Password is existed or not
#define CREATINGPASSWORD 0x12		// Signal to Creating Password and Rewrite in memory
#define SAVEDPASSWORD 0x13			// Password is correct
#define WRONGPASSWORD 0x14			// Wrong Password
#define PASSWORD_COMFIRM 0x15		// Memory had to Write Safe
#define PASSWORD_NOTCOMFIRM 0x17	// Error while writing on memory
#define CHECKPASSWORD 0x20			// Signal to Read Password and Compare it with memory (Real Password)
#define EREASEPASSWORD 0x21			// Remove memory
#define OPENBUZZER 0x25				// Signal to Open buzzer
#define ROTATE_MOTOR 0x30			// signal to Start Open Door
#define HMI_READY 0x35				// Ready Signal For HML
#define CONTROL_READY 0x40			// Ready Signal For Controller
//METHOD PROTOTYPES
void Receive_Password(uint8 ptr[]);
void ReadPasswordFormEEPROM(uint8 ptr[]);
uint8 CompareTheTwoPasswords();
void CheckPassword();
void CreatingPassword();
void UnLock_Door_15_S();
void freeze_3_Seconds();
void OpeningDoor();
void Buzzer_Cry_60_Seconds();
void OpenBuzzer();


#endif /* CONTROL_ECU_H_ */
