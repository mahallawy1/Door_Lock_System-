/*
 * Control_ECU.c
 *
 *  Created on: 3 Nov 2023
 *      Author: Abdelrahman Mahalawy
 */

#include "Control_ECU.h"

/*	global Var.*/
uint8 Password[5]={0};
uint8 Password2[5]={0};
uint8 freeze=0;
Timer1_ConfigType Config={0,7813,Prescalar_1024,CTC_Mode};





void Receive_Password(uint8 ptr[]){
	for(int i=0;i<5;i++){
			uint8  x =UART_recieveByte();
			ptr[i]=x;
		}
}

void ReadPasswordFormEEPROM(uint8 ptr[]){
	for(int i=0;i<5;i++){
			EEPROM_readByte(i,&ptr[i]);
			_delay_ms(10);
		}
}




uint8 CompareTheTwoPasswords(){
	for(uint8 counter=0;counter<5;counter++){
			if(Password[counter]!=Password2[counter]){
				return 0;
			}
		}
	return 1;
}



void CheckPassword(){
	uint8 flag=1;
	Receive_Password(Password);
	ReadPasswordFormEEPROM(Password2);
	flag=CompareTheTwoPasswords();
	if(flag){
		UART_sendByte(SAVEDPASSWORD);
	}
	else{
		UART_sendByte(WRONGPASSWORD);
	}
}




void CreatingPassword(){
	uint8 flag=1;
	Receive_Password(Password);
	Receive_Password(Password2);

	flag=CompareTheTwoPasswords();
	if(flag){
		for(uint8 counter=0;counter<5;counter++){
			EEPROM_writeByte(counter, Password[counter]); /* Write 0x0F in the external EEPROM */
			_delay_ms(10);
		}
		EEPROM_writeByte(0x0100,1);
		_delay_ms(10);
		UART_sendByte(SAVEDPASSWORD);
	}
	else{
		UART_sendByte(WRONGPASSWORD);
	}

}


void UnLock_Door_15_S(){
	static uint8 count=0;
	count++;
	if(count==14){
	count=0;
	freeze=0;
	Timer1_deInit();
	}
}




void freeze_3_Seconds(){
	static uint8 count=0;
		count++;
		if(count==2){
		count=0;
		freeze=0;
		Timer1_deInit();
		}
}


void OpeningDoor(){
	Timer1_init(&Config);
	Timer1_setCallBack(&UnLock_Door_15_S);
	DcMotor_Rotate(MOTOR_CLOCKWISE, 255);
	freeze=1;
	while(freeze);
	Timer1_init(&Config);
	Timer1_setCallBack(&freeze_3_Seconds);
	DcMotor_Rotate(MOTOR_STOP, 0);
	freeze=1;
	while(freeze);
	Timer1_init(&Config);
	Timer1_setCallBack(&UnLock_Door_15_S);
	DcMotor_Rotate(MOTOR_ANTICLOCKWISE, 255);
	freeze=1;
	while(freeze);
	DcMotor_Rotate(MOTOR_STOP, 0);
}



void Buzzer_Cry_60_Seconds(){
	static uint8 count=0;
	count++;
	if(count==59){
		count=0;
		freeze=0;
		Timer1_deInit();
	}
}


void OpenBuzzer(){
	Timer1_init(&Config);
	Timer1_setCallBack(&Buzzer_Cry_60_Seconds);
	Buzzer_on();
	freeze=1;
	while(freeze);
	Buzzer_off();
}

