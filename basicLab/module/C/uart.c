//**************************************//
//  實驗: UART0 (鮑率9600)
//  腳位: P3.4(TX)、P3.5(RX)
//  實驗結果: 印出 "hello" 至終端機
//**************************************//
#include "../../main.h"

void UART_initIO() {
	P3SEL |= BIT4 + BIT5;	// UATR0 模組
	P3DIR |= BIT4;			// P3.4(Tx) dir output
	P3OUT &= BIT4;			// P3.4 = 0
	_EINT();
}

void UART_init() {
	U0CTL |= CHAR;		// 一筆資料8位元
	U0TCTL = SSEL0;		// ACLK = 32767Hz
	U0BR0 = 0x03;		// 32767Hz / 9600 = 3.41
	U0BR1 = 0x00;
	U0MCTL = 0x4a;
	U0CTL &= ~SWRST;	// 初始化U1CTL
}

void UART_putStr(char c[], int strLength) {
	UINT16 i;
	for (i = 0; i < strLength; i++)
		UART_putChar(c[i]);
}

void UART_putChar(unsigned char c) {
	ME1 |= UTXE0;
	U0TXBUF = c;
	while (!(U0TCTL & TXEPT))
		; //等待8bit送滿
	ME1 &= ~UTXE0;
}

int UART_getChar(void) {
	int c = 0;
	while (!(IFG1 & URXIFG0))
		; //等待對方送，兩個一樣才會跳開
	c = U0RXBUF;
	return c;
}
