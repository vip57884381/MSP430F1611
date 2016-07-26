#include "../../main.h"

void _24C02_initIO() {  
	P1DIR |= (BIT5 + BIT6);
	P1OUT &= ~(BIT5 + BIT6);
}

void start() {
	SDA_HIGH; 
	wait(1);
	SCL_HIGH; 
	wait(1);
	SDA_LOW; 
	wait(1);
	SCL_LOW;  
	wait(1); 
}

/* SDA=1 , SDA •øΩt≈‹§∆
 * SDA      _
 *      ___/ 
 * SCL    ___
 *      _/
 */
void stop() {
	SDA_LOW; 
	wait(1);
	SCL_HIGH; 
	wait(1);
	SDA_HIGH; 
	wait(1);
	SCL_LOW;  
	wait(1);
}

void writeAck() {
	SDA_LOW; 
    wait(1);
	SCL_HIGH; 
    wait(1);
	SCL_LOW; 
    wait(1);
}

void noAck() {  
	SDA_HIGH;  
    wait(1);
	SCL_HIGH; 
    wait(1);
	SCL_LOW;
	wait(1);
}

UINT8 readAck() {
	UINT8 ack;
	SDA_LOW; 
    wait(1);
    P1DIR &= ~(SDA);
	SCL_HIGH; 
    wait(1);
	ack = (P1IN & SDA); 
	SCL_LOW; 
    wait(1);
    P1DIR |= SDA;
    wait(1);
	return ack;
}

void write8Bit(UINT8 input) {
	UINT8 i;    
	for (i=0;i<8;i++) 
    {
        if((input&0x80)==0x80)
            SDA_HIGH;
        else
            SDA_LOW;
        wait(1);
		SCL_HIGH;
        wait(1);
		SCL_LOW;
        wait(1);
		input<<=1;
	}
}

void write24c02(char *wData,UINT8 romAdr,UINT8 bit) 
{	
	UINT8 i;
	start();
	write8Bit(writeDeviceAdr);
	readAck();
	write8Bit(romAdr);
	readAck();
	for (i=0;i<bit;i++) {
		write8Bit(*wData);
		readAck();
		wData++;
		wait(1);
	}
	stop();
}

char read8Bit() {
	UINT8 i;
	UINT8 readByte;
	readByte = 0;
    SDA_HIGH;
    wait(1);
    P1DIR &= ~(SDA);
	for (i=0;i<8;i++) {
		readByte <<= 1;
		SCL_HIGH; 
        wait(1);
        if((P1IN & SDA)==SDA)
            readByte |= 0x01;
		SCL_LOW; 
        wait(1);
	}
	P1DIR |= SDA;
	wait(1);
	return(readByte);
}

void read24c02(char *rData,UINT8 romAdr,UINT8 bit) 
{
	UINT8 i;
	start();
	write8Bit(writeDeviceAdr);
	readAck();
	write8Bit(romAdr);
	readAck();
	start();
	write8Bit(readDeviceAdr);
	readAck();
	for (i=0;i<bit;i++) {
		*rData=read8Bit();
		writeAck();
		rData++;
	}
	noAck();
	stop();
}
