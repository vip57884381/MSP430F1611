#include "main.h"

// ※ timer , 7SEG + Timer
void _main_timer(){
	WDTCTL = WDTPW + WDTHOLD;			// Stop watchdog timer to prevent time out reset

	_7SEG_initIO();
	
	while(1){
		_7SEG();
	}
}

// ※ interrupt , 4_7SEG + Timer
void _main_interrupt(){
	WDTCTL = WDTPW + WDTHOLD;			// Stop watchdog timer to prevent time out reset
	_4_7SEG_initIO();
	_4x4keyboard_initIO();
	while(1){
		scanner();
		_4_7SEG(getKeyVal(0));
		_4_7SEG(getKeyVal(1));
		_4_7SEG(getKeyVal(2));
		_4_7SEG(getKeyVal(3));
	}
}

// ※ LCD
char LCDROW1[16] = " This is a 2x16 "; // LCM第一行字串
char LCDROW2[16] = "line LCD Display"; // LCM第二行字串
void _main_LCD(){
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent time out reset

	LCD_initIO(); // LCD IO 初始化
	LCD_init(); // LCD 初始化
	LCD_writeString(0x80, 16, LCDROW1); // 寫入字串table1到LCD第一行
	LCD_writeString(0xc0, 16, LCDROW2); // 寫入字串table2到LCD第二行
	
	while(1){
	}
}

// ※ ADC , ADC + _4_7SEG
UINT16 tmpResult;
int temp[4]; // 存 4_7EG的值
float Vref = 2.31; // ADC 參考電壓
void _main_ADC(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
	tmpResult = 0;
	
	ADC0804_initIO();
	_4_7SEG_initIO();
	
	while(1){
		tmpResult = (ADC0804_getValue()*(Vref * 2 *1000) / 256); // Vi 電壓計算
		temp[0]=tmpResult/1000; // 個位數
		temp[1]=(tmpResult%1000)/100; // 小數點第一位
		temp[2]=(tmpResult%100)/10; // 小數點第二位
		temp[3]=tmpResult%10; // 小數點第三位
		_4_7SEG(temp[0]);
		_4_7SEG(temp[1]);
		_4_7SEG(temp[2]);
		_4_7SEG(temp[3]);
	}
}

// ※ DAC , DAC + LCD
char* outLcdRow1;
char* outLcdRow2;
char LCDROW1_title[16] = "wData = ";
char LCDROW2_title[16] = "rData = ";
UINT8 i;
void _main_DAC(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset

	LCD_initIO(); // LCD IO 初始化
	LCD_init(); // LCD 初始化

	while(1){
		for(i = 0 ; i < 255 ; i++)
		{
			DAC08_setValue(i);
			outLcdRow1 = decToBin(i);
			outLcdRow2 = numToStr(i);
			LCD_writeString(0x80, 16, outLcdRow1); // 寫入字串table1到LCD第一行
			LCD_writeString(0xc0, 16, outLcdRow2); // 寫入字串table2到LCD第二行
			wait(100);
		}
	}
}

// ※ UART
char table[]="hello\r\n" ;
void _main_UART(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
    UART_initIO();
	UART_init();
	
	while(1){
		UART_putStr(table,strlen(table));
    	wait(500);  // 延遲500ms
	}
}

// ※ SPI , SPI + LCD
//char* outLcdRow1;
//char* outLcdRow2;
char save_to_eeprom[8] = "12345678";
char read_from_eeprom[8] = "00000000";
//char LCDROW1_title[16] = "wData = ";
//char LCDROW2_title[16] = "rData = ";
void _main_SPI(){
  WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
  
  _93C46_initIO();
  LCD_initIO(); // LCD IO 初始化
  LCD_init(); // LCD 初始化
  
  UINT8 i = 0;
  UINT8 strMaxLen = 8;
  
  EWEN();                  // 致能EEPROM寫入及清除
  ERAL();                  // EEPROM清除全部記憶體
  for(i=0;i<strMaxLen;i++)	// 寫入8筆資料
    write93C46(i,save_to_eeprom[i]);	// 寫入位址及8-bit資料
  EWDS();				   // 禁能EEPROM寫入及清除
  for(i=0;i<strMaxLen;i++) // 讀取8筆資料
    read_from_eeprom[i] = read93C46(i);   // 讀取EEPROM的8-bit資料由LED輸出
  
  outLcdRow1 = string_concat(LCDROW1_title,save_to_eeprom);
  outLcdRow2 = string_concat(LCDROW2_title,read_from_eeprom);
		
  LCD_writeString(0x80, 16, outLcdRow1); // 寫入字串table1到LCD第一行
  LCD_writeString(0xc0, 16, outLcdRow2); // 寫入字串table2到LCD第二行
  
  while(1)  {
  }
}

// ※ I2C , I2C + LCD
//char* outLcdRow1;
//char* outLcdRow2;
// char save_to_eeprom[8] = "12345678";
// char read_from_eeprom[8] = "00000000";
// char LCDROW1_title[8] = "wData = ";
// char LCDROW2_title[8] = "rData = ";
void _main_I2c(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
    _24C02_initIO();
    LCD_initIO(); // LCD IO 初始化
	LCD_init(); // LCD 初始化
	 
	write24c02(save_to_eeprom,0,8);
	read24c02(read_from_eeprom,0,8); 
	
	outLcdRow1 = string_concat(LCDROW1_title,save_to_eeprom);
	outLcdRow2 = string_concat(LCDROW2_title,read_from_eeprom);
	
	LCD_writeString(0x80, 16, outLcdRow1); // 寫入字串table1到LCD第一行
	LCD_writeString(0xc0, 16, outLcdRow1); // 寫入字串table2到LCD第二行
	while(1){
	}
}

void main() {
	// 實驗 code 放這
	_main_ADC();
}
