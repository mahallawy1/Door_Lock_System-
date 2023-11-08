/******************************************************************************
 *
 * Module: HML.ECU
 *
 * File Name: main.c
 *
 * Description:	application main file
 *
 * Author: Abdelrahman Mahalawy
 *
 *******************************************************************************/
#include "HMU_ECU.h"


int main(){


	SET_BIT(SREG,7);
	UART_ConfigType UartConfig={Eight_Bit,Disabled,One_Bit,9600};


	UART_init(&UartConfig);
	LCD_init();

	while(UART_recieveByte()!=CONTROL_READY);

		UART_sendByte(REG_PASSWORD);
 		uint8 order=UART_recieveByte();

		if(order==PASSWORD_COMFIRM){
			uint8 key2='a';
			 LCD_clearScreen();
			 LCD_displayStringRowColumn(0,0,"+  : Open Door");
			 LCD_displayStringRowColumn(1,0,"-  : Change Pass");
			while(key2!='+' && key2!='-'){
				key2=KEYPAD_getPressedKey();
			}


			uint8 try_again=3;
			uint8 answer;
			do{
			try_again--;
			UART_sendByte(CHECKPASSWORD);
			Check_Password();
			answer=UART_recieveByte();
			}
			while(try_again>0 && answer!=SAVEDPASSWORD);

			if(try_again==0 && answer==SAVEDPASSWORD){
				try_again=3;
			}

			if(key2=='+' &&try_again>0){

				UART_sendByte(ROTATE_MOTOR);
				OpenDoor();

				uint8 answerOfMotor;
				do{

				  answerOfMotor=UART_recieveByte();
				}while(answerOfMotor!=ROTATE_MOTOR);
			}


			else if (key2=='-'&&try_again>0){

				UART_sendByte(EREASEPASSWORD);
				uint8 answerOfDeletedPassword;
				do{

					answerOfDeletedPassword =UART_recieveByte();
				}while(answerOfDeletedPassword!=EREASEPASSWORD);
			}


			else{

				UART_sendByte(OPENBUZZER);

				Error_And_Input();
				uint8 answerOfBuzzer;
				do{

					answerOfBuzzer=UART_recieveByte();

				}
				while(answerOfBuzzer!=OPENBUZZER);
			}
		}
		else{
			uint8 answer;
			do{

			UART_sendByte(CREATINGPASSWORD);
			New_Password();

			answer=UART_recieveByte();
			}while(answer!=SAVEDPASSWORD);
		}
	}





