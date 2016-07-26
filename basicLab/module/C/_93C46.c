//**************************************//
//  實驗: SPI
//  腳位: SPI
//        OUT P5.4(CS)、P5.5(CK)、P5.6(DI)
//            X2D36   、X2D37   、X2D38
//        IN  P5.7(DO)
//            X2D39
//**************************************//
#include "../../main.h"

void _93C46_initIO() {
  P5DIR |= (BIT4 + BIT5 + BIT6);
  P5OUT &= ~(BIT4 + BIT5 + BIT6);
  DI_93C46_HIGH;
  DO_93C46_HIGH;
  CS_93C46_LOW;
  CK_93C46_LOW;
}

void clock93C46() {
	CK_93C46_HIGH; // SK=1;
	wait(1); // 延遲1ms
	CK_93C46_LOW; // SK=0;
	wait(1); // 延遲1ms
}

void EWEN() // EEPROM寫入及清除致能
{
	CS_93C46_HIGH; // CS=1; 開啟EEPROM晶片
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x60); // 送入操作碼0及指令，致能抹除/寫入動作
	CS_93C46_LOW; // CS=0; 關閉EEPROM晶片
	wait(1); // 延遲1ms
}

void EWDS() // EEPROM寫入及清除禁能
{
	CS_93C46_HIGH; // CS=1; 開啟EEPROM晶片
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x00); // 送入操作碼0及指令，禁能抹除/寫入動作
	CS_93C46_LOW; // CS=0; 關閉EEPROM晶片
	wait(1); // 延遲1ms
}

void ERAL() // EEPROM清除全部記憶體
{
	CS_93C46_HIGH; // CS=1; 開啟EEPROM晶片
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x40); // 送入操作碼0及指令，禁能抹除/寫入動作
	CS_93C46_LOW; // CS=0; 關閉EEPROM晶片
	wait(1); // 延遲1ms
}

void send93C46(UINT8 Addr) // 送入93C46串列EEPROM資料
{
	UINT8 i = 0;
	for (i = 0; i < 8; i++) // 送入8-bit
	{
		if (Addr & 0x80) // 若bit7=1，
			DI_93C46_HIGH; // 則DI=1
		else
			// 若bit7=0，
			DI_93C46_LOW; // 則DI=0
		clock93C46(); // 串列時脈，bit送入EEPROM
		Addr <<= 1; // 位址左移
	}
}

void write93C46(UINT8 Addr, UINT8 ch)// 寫入93C46串列EEPROM資料
{
	CS_93C46_HIGH; // CS=1; 開啟EEPROM晶片
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x80 + Addr); // 送入操作碼1及位址
	send93C46(ch); // 寫入資料
	CS_93C46_LOW; // CS=0; 關閉EEPROM晶片
}

UINT8 read93C46(UINT8 Addr)// 讀取93C46串列EEPROM資料
{
	UINT8 ch = 0;
	UINT8 i = 0;

	CS_93C46_HIGH;// CS=1; 開啟EEPROM晶片
	DI_93C46_HIGH;// DI=1;
	clock93C46();// clock
	DI_93C46_HIGH;// DI=1;
	clock93C46();// clock
	send93C46(0x00 + Addr); // 送入操作碼0及位址
	for (i = 0; i < 8; i++) // 讀取8bit到ch
			{
		clock93C46(); // clock
		ch = ch << 1; // 位址左移
		if (DO_93C46_HIGH) // 若 DO = 1，
			ch = ch | 0x01; // ch = 1
	}
	CS_93C46_LOW; // CS=0; 關閉EEPROM晶片
	return ch; // 將8-bit資料送回主程式
}
