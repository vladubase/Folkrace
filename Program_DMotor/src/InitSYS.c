/****
	*	@name		DMotor_folkrace
	*	@file 		InitSYS.c
	*
	*	@author 	Uladzislau 'vladubase' Dubatouka
	*				<vladubase@gmail.com>
	*
*****/


/************************************** Includes **************************************/

#include "../inc/InitSYS.h"


/************************************** Function **************************************/

void InitSYS (void) {
	PORTC = 0x00;
	DDRC = 0x00;
	DDRC |= (1 << DDC3) | (1 << DDC2) | (1 << DDC1) | (1 << DDC0);
}
