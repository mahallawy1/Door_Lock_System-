/*
 * HMU_ECU.c
 *
 *  Created on: 7 Nov 2023
 *      Author: Abdelrahman Mahalawy
 */

#include "HMU_ECU.h"

uint8 freeze=0;
uint8 key;
uint8 Password[5]={0};
uint8 PasswordConfirm[5]={0};
Timer1_ConfigType Config={0,7813,Prescalar_1024,CTC_Mode};




void First_Error_Message(void){
	static uint8 count=0;
	count++;
	freeze=1;
	if(count ==14){
		freeze=0;
		count=0;
		Timer1_deInit();
	}
}


void First_Display(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz enter pass:");
	LCD_moveCursor(1,0);
}



void Reenter_Display(void){
	LCD_displayStringRowColumn(0,0,"Plz re-enter pass:");
	LCD_displayStringRowColumn(1,0,"Same Pass:");
}



void GetPass(uint8 Ptr[]){
	for(uint8 counter=0;counter<5;counter++){
			key=KEYPAD_getPressedKey();
			if((key <= 9) && (key >= 0)){
				Ptr[counter]=key;
				LCD_displayCharacter('*');
				_delay_ms(250);
			}
			else{
				counter--;
			}
		}
}


void Send_Password(uint8 Ptr[]){
	for(uint8 counter=0;counter<5;counter++){
			UART_sendByte(Ptr[counter]);
		}
}


void Wait_For_EnterKey(){
	while(key!=13){
			key=KEYPAD_getPressedKey();
	}
}


void Check_Password(){
	First_Display();
	GetPass(PasswordConfirm);
	Wait_For_EnterKey();
	Send_Password(PasswordConfirm);
}



void New_Password(){
	First_Display();
	GetPass(Password);
	Wait_For_EnterKey();

	Reenter_Display();
	GetPass(PasswordConfirm);
	Wait_For_EnterKey();

	Send_Password(Password);
	_delay_ms(10);
	Send_Password(PasswordConfirm);
}




void UnLock_Door(){
	static uint8 count=0;
	count++;
	if(count==14){
	count=0;
	freeze=0;
	Timer1_deInit();
	}
}




void Freeze_Door(){
	static uint8 count=0;
	count++;
	if(count==2){
		count=0;
		freeze=0;
		Timer1_deInit();
	}
}


void Wait_FreezeEnd(){
	freeze=1;
	while(freeze);
}



void OpenDoor(){
	LCD_clearScreen();
	Timer1_init(&Config);
	Timer1_setCallBack(&UnLock_Door);
	LCD_displayStringRowColumn(0,0,"Door is Unlocking");
	Wait_FreezeEnd();

	LCD_clearScreen();
	Timer1_init(&Config);
	Timer1_setCallBack(&Freeze_Door);
	LCD_displayStringRowColumn(0,0,"Holding");
	Wait_FreezeEnd();

	LCD_clearScreen();
	Timer1_init(&Config);
	Timer1_setCallBack(&UnLock_Door);
	LCD_displayStringRowColumn(0,0,"Door is Locking");
	Wait_FreezeEnd();
}




void View_Error(){
	static uint8 count=0;
	count++;
	if(count==59){
		count=0;
		freeze=0;
		Timer1_deInit();
	}
}




void Error_And_Input(){
	LCD_clearScreen();
	Timer1_init(&Config);
	Timer1_setCallBack(&View_Error);
	LCD_displayStringRowColumn(0,0,"ERROR!!");
	Wait_FreezeEnd();
}
