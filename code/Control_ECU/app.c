/******************************************************************************
 *
 * Module: Control_ECU
 *
 * File Name: main.c
 *
 * Description:	application main file
 *
 * Author: Abdelrahman Mahalawy
 *
 *******************************************************************************/

#include "Control_ECU.h"


int main(){





	TWI_ConfigType 	TwiConfig={FastMode,1};
	 SET_BIT(SREG,7);
	UART_ConfigType UartConfig={Eight_Bit,Disabled,One_Bit,9600};


	UART_init(&UartConfig);
	Buzzer_init();
	TWI_init(&TwiConfig);
	DcMotor_Init();

	uint8 SavedPassword;
	EEPROM_writeByte(0x0100,0);

	_delay_ms(10);
	UART_sendByte(CONTROL_READY);

	while(1){
		uint8 order=UART_recieveByte();
		/*
		 * Here We check the flag in address 100 in EEPROM
		 * to see if there is a password or no in  EEPROM
		 * then Send if there is a password or no
		 * */
		if(order==REG_PASSWORD){
			EEPROM_readByte(0x0100,&SavedPassword);
			if(SavedPassword)
				UART_sendByte(PASSWORD_COMFIRM);
			else
				UART_sendByte(PASSWORD_NOTCOMFIRM);
		}

		/*
		 * here if we can order to Creating password
		 * we read the 2 passwords form uart then write the password on EEPROM
		 * */
		else if(order==CREATINGPASSWORD){
			CreatingPassword();
		}
		else if(order==CHECKPASSWORD){
			CheckPassword();
		}
		else if(order==ROTATE_MOTOR){
			OpeningDoor();
			UART_sendByte(ROTATE_MOTOR);
		}

		// To Erease the password just Clear the Flag and overwrite on it
		else if(order==EREASEPASSWORD){
			EEPROM_writeByte(0x0100,0);
			_delay_ms(10);
			UART_sendByte(EREASEPASSWORD);
		}
		else if(order==OPENBUZZER){
			OpenBuzzer();
			UART_sendByte(OPENBUZZER);
		}
	}

}
