/*
 * HMU_ECU.h
 *
 *  Created on: 7 Nov 2023
 *      Author: Abdelrahman Mahalawy
 */

#ifndef HMU_ECU_H_
#define HMU_ECU_H_
//INCLUDES

#include "lcd.h"
#include "timer.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include <util/delay.h>
#include "keypad.h"
#include "uart.h"
#include "avr/io.h"
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
void First_Error_Message(void);
void First_Display(void);
void Reenter_Display(void);
void GetPass(uint8 Ptr[]);
void Send_Password(uint8 Ptr[]);
void Wait_For_EnterKey();
void Check_Password();
void New_Password();
void UnLock_Door();
void Freeze_Door();
void Wait_FreezeEnd();
void OpenDoor();
void View_Error();
void Error_And_Input();

#endif /* HMU_ECU_H_ */
