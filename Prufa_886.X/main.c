/*
 * File:   main.c
 * Author: zap
 *
 * Created on 5. ágúst 2011, 20:39
 */

//#define _16F886 //ser compilerinn um tetta?
#include "pic.h"

#define		E			RA5
#define		RW			RA3
#define		RS			RA2

#define		CLR_DISP		0x01
#define		DISP_ON			0x0C
#define		DISP_OFF		0x08
#define		CUR_HOME        0x02
#define		CUR_OFF 		0x0C
#define 	CUR_ON_UNDER    0x0E
#define		CUR_ON_BLINK    0x0F
#define 	CUR_LEFT        0x10
#define		CUR_RIGHT       0x14
#define		CUR_UP  		0x80
#define		CUR_DOWN		0xC0
#define		ENTER           0xC0
#define		DD_RAM_ADDR		0x80
#define		DD_RAM_ADDR2	0xC0




__CONFIG(INTIO & WDTDIS & PWRTDIS /*ATH*/ & MCLREN & UNPROTECT & DUNPROTECT);

void init(void);


unsigned  int dly;
unsigned  int i;
unsigned  char data;

unsigned char OlimexMsg[] = " www.olimex.com ";


//delay time = (cntr*2)+3 (in us for 20MHz)
//FULL OPTIMIZATION of C compilator(10 level, enable post-pass optimisation)
void Delay(unsigned int cntr) {
	for (dly=0; dly!=cntr; dly++) {
		asm("nop");
		asm("nop");
		asm("nop");
	}
}

//delay time is ~ 1ms
void DelayMs (unsigned char e)
{
	while(--e) {
		//Delay(DELAY_1000us);
            asm("NOP");
	 }
}



void E_Pulse(void) {
	E=1;
	asm("nop");
	asm("nop");
	asm("nop");
	E=0;
}

// Init LCD  after reset
void InitLCD(void) {

	INTCON 	= 0x0;			// Disable inerupt
//MCON 	= 0x07;		    // Comparators Off
	ADCON1  = 0x06;			// Port as Digital IO
	TRISA2 	= 0;			// RS pin as output
	TRISA3 	= 0;			// RW pin as output
	TRISA5 	= 0;			// E pin as output
	TRISC	= 0xF0;			// D4-D7 as output


	RS=0;
	RW=0;
	DelayMs(110);
	PORTC=0b00000011;
	E_Pulse();
	DelayMs(10);
	PORTC=0b00000011;
	E_Pulse();
	DelayMs(10);
	PORTC=0b00000011;
	E_Pulse();
	DelayMs(10);
	PORTC=0b00000010;
	E_Pulse();
}

// Send char to LCD
LCDSendChar(unsigned char c) {

	DelayMs(2);
	//get upper nibble
	data = c & 0b11110000;
	//set D4-D7
	data = data >> 4;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=1;
	//toggle E for LCD
	E_Pulse();
	// get lower nibble
	data = c & 0b00001111;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=1;
	//toggle E for LCD
	E_Pulse();
}

// Send command to LCD
LCDSendCmd(unsigned char c) {

	DelayMs(2);
	//get upper nibble
	data = c & 0b11110000;
	//set D4-D7
	data = data >> 4;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=0;
	//toggle E for LCD
	E_Pulse();
	// get lower nibble
	data = c & 0b00001111;
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=0;
	//toggle E for LCD
	E_Pulse();
}

void LCDSendStr(unsigned char* str) {

	i=0;
	while(str[i]) {
		LCDSendChar(str[i]);
		i++;
	}
}


int main(void) {
    
    return 0;
}


void init()
{
    int i =0;
}