#include "main.h"

// �� timer , 7SEG + Timer
void _main_timer(){
	WDTCTL = WDTPW + WDTHOLD;			// Stop watchdog timer to prevent time out reset

	_7SEG_initIO();
	
	while(1){
		_7SEG();
	}
}

// �� interrupt , 4_7SEG + Timer
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

// �� LCD
char LCDROW1[16] = " This is a 2x16 "; // LCM�Ĥ@��r��
char LCDROW2[16] = "line LCD Display"; // LCM�ĤG��r��
void _main_LCD(){
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent time out reset

	LCD_initIO(); // LCD IO ��l��
	LCD_init(); // LCD ��l��
	LCD_writeString(0x80, 16, LCDROW1); // �g�J�r��table1��LCD�Ĥ@��
	LCD_writeString(0xc0, 16, LCDROW2); // �g�J�r��table2��LCD�ĤG��
	
	while(1){
	}
}

// �� ADC , ADC + _4_7SEG
UINT16 tmpResult;
int temp[4]; // �s 4_7EG����
float Vref = 2.31; // ADC �Ѧҹq��
void _main_ADC(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
	tmpResult = 0;
	
	ADC0804_initIO();
	_4_7SEG_initIO();
	
	while(1){
		tmpResult = (ADC0804_getValue()*(Vref * 2 *1000) / 256); // Vi �q���p��
		temp[0]=tmpResult/1000; // �Ӧ��
		temp[1]=(tmpResult%1000)/100; // �p���I�Ĥ@��
		temp[2]=(tmpResult%100)/10; // �p���I�ĤG��
		temp[3]=tmpResult%10; // �p���I�ĤT��
		_4_7SEG(temp[0]);
		_4_7SEG(temp[1]);
		_4_7SEG(temp[2]);
		_4_7SEG(temp[3]);
	}
}

// �� DAC , DAC + LCD
char* outLcdRow1;
char* outLcdRow2;
char LCDROW1_title[16] = "wData = ";
char LCDROW2_title[16] = "rData = ";
UINT8 i;
void _main_DAC(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset

	LCD_initIO(); // LCD IO ��l��
	LCD_init(); // LCD ��l��

	while(1){
		for(i = 0 ; i < 255 ; i++)
		{
			DAC08_setValue(i);
			outLcdRow1 = decToBin(i);
			outLcdRow2 = numToStr(i);
			LCD_writeString(0x80, 16, outLcdRow1); // �g�J�r��table1��LCD�Ĥ@��
			LCD_writeString(0xc0, 16, outLcdRow2); // �g�J�r��table2��LCD�ĤG��
			wait(100);
		}
	}
}

// �� UART
char table[]="hello\r\n" ;
void _main_UART(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
    UART_initIO();
	UART_init();
	
	while(1){
		UART_putStr(table,strlen(table));
    	wait(500);  // ����500ms
	}
}

// �� SPI , SPI + LCD
//char* outLcdRow1;
//char* outLcdRow2;
char save_to_eeprom[8] = "12345678";
char read_from_eeprom[8] = "00000000";
//char LCDROW1_title[16] = "wData = ";
//char LCDROW2_title[16] = "rData = ";
void _main_SPI(){
  WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
  
  _93C46_initIO();
  LCD_initIO(); // LCD IO ��l��
  LCD_init(); // LCD ��l��
  
  UINT8 i = 0;
  UINT8 strMaxLen = 8;
  
  EWEN();                  // �P��EEPROM�g�J�βM��
  ERAL();                  // EEPROM�M�������O����
  for(i=0;i<strMaxLen;i++)	// �g�J8�����
    write93C46(i,save_to_eeprom[i]);	// �g�J��}��8-bit���
  EWDS();				   // �T��EEPROM�g�J�βM��
  for(i=0;i<strMaxLen;i++) // Ū��8�����
    read_from_eeprom[i] = read93C46(i);   // Ū��EEPROM��8-bit��ƥ�LED��X
  
  outLcdRow1 = string_concat(LCDROW1_title,save_to_eeprom);
  outLcdRow2 = string_concat(LCDROW2_title,read_from_eeprom);
		
  LCD_writeString(0x80, 16, outLcdRow1); // �g�J�r��table1��LCD�Ĥ@��
  LCD_writeString(0xc0, 16, outLcdRow2); // �g�J�r��table2��LCD�ĤG��
  
  while(1)  {
  }
}

// �� I2C , I2C + LCD
//char* outLcdRow1;
//char* outLcdRow2;
// char save_to_eeprom[8] = "12345678";
// char read_from_eeprom[8] = "00000000";
// char LCDROW1_title[8] = "wData = ";
// char LCDROW2_title[8] = "rData = ";
void _main_I2c(){
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer to prevent time out reset
	
    _24C02_initIO();
    LCD_initIO(); // LCD IO ��l��
	LCD_init(); // LCD ��l��
	 
	write24c02(save_to_eeprom,0,8);
	read24c02(read_from_eeprom,0,8); 
	
	outLcdRow1 = string_concat(LCDROW1_title,save_to_eeprom);
	outLcdRow2 = string_concat(LCDROW2_title,read_from_eeprom);
	
	LCD_writeString(0x80, 16, outLcdRow1); // �g�J�r��table1��LCD�Ĥ@��
	LCD_writeString(0xc0, 16, outLcdRow1); // �g�J�r��table2��LCD�ĤG��
	while(1){
	}
}

void main() {
	// ���� code ��o
	_main_ADC();
}
