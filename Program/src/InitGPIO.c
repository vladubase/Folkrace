/****
	*	@name		LCD1602
	*	@file 		InitGPIO.c
	*
	*	@author 	Uladzislau 'vladubase' Dubatouka
	*				<vladubase@gmail.com>
	*
*****/


/************************************** Includes **************************************/

#include "inc/InitGPIO.h"


/************************************** Function **************************************/

void InitGPIO (void) {
	PORTC = 0x00;
	DDRC = 0x00;
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);
}
