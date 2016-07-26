//**************************************//
//  實驗: LCD
//  腳位: OUT P3.2(EN)、P3.1(RW)、P3.0(RS)
//            X2D22   、X2D13   、X2D12
//        OUT P4.0 、P4.1 、P4.2 、P4.3 、P4.4 、P4.5 、P4.6 、P4.7
//            X2D14、X2D15、X2D16、X2D17、X2D18、X2D19、X2D20、X2D21
//  實驗結果: LCD顯示 第一行 1234567890123456
//                   第二行 ABCDEFGHIJKLMNOP
//**************************************//
#include "../../main.h"

void LCD_initIO() {
	P3DIR |= (BIT0+BIT1+BIT2);	// P3.0~3.2 dir output
	P4DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7); // P4 dir output
	P3OUT &= ~(BIT0+BIT1+BIT2);	// P3.0~3.2 = 0
	P4OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7); // P4 = 0
}

// LCM啟始
void LCD_init() {
	LCD_writeInst(0x30);
	LCD_writeInst(0x30);
	LCD_writeInst(0x30);
	LCD_writeInst(0x38); // 8bit傳輸，顯示2行，5X7字型
	LCD_writeInst(0x08); // 顯示完游標右移，游標移位禁能
	LCD_writeInst(0x01); // 清除顯示
	LCD_writeInst(0x06); // 顯示完游標右移，游標移位禁能
	LCD_writeInst(0x0c); // 開啟顯示，不顯示游標，游標不閃爍
}

// 寫入指令到LCD
void LCD_writeInst(UINT8 comm) {
	LCD_checkBF();
	P4OUT = comm;	//位址送到BUS
	LCD_RS_LOW;
	LCD_RW_LOW;
	LCD_EN_HIGH;	//寫入指令到LCD
	LCD_checkBF();
	LCD_EN_LOW;		//禁能LCD
}

// 檢查忙碌函數
void LCD_checkBF() {
	UINT8 tmp1;
	LCD_EN_LOW;		// 禁能LCD
	do {
		LCD_RS_LOW;
		LCD_RW_HIGH;
		LCD_EN_HIGH;
		wait(1);
		P4DIR = 0x00;
		tmp1 = P4IN;
		tmp1 &= 0x80;
	} while (tmp1 == 0x80);
	P4DIR = 0xff;
}

// 寫入資料到LCM
void LCD_writeChar(UINT8 data) {
	LCD_checkBF();
	P4OUT = data; // 資料送到BUS
	LCD_RS_HIGH;
	LCD_RW_LOW;
	LCD_EN_HIGH; //寫入資料到LCD
	LCD_checkBF();
	LCD_EN_LOW; // 禁能LCD
}

// 寫入字串到LCD函數開始
void LCD_writeString(UINT8 col, UINT8 count, char table[]) {
	UINT8 i;
	LCD_writeInst(col);
	for (i = 0; i < count; i++)
		LCD_writeChar(table[i]);
}

void LCD_transStr(char *in , char *out) {
	UINT8 i;
	UINT8 strMaxLen = 16;
	for (i = 0 ; i < strMaxLen ; i++)
	{
		if( i < strlen(in))
			out[i] = in[i];
		else
			out[i] = ' ';
	}
	out[strMaxLen] = '\0';
}

/* string_concat [字串相加]
 * 將 str1 與 str2 相加，並返回新的字串
 * */
char *string_concat(char *str1, char *str2) {
    // 計算所需的陣列長度
    int length=strlen(str1)+strlen(str2)+1;
  
    // 產生新的陣列空間
    char *result = (char*)malloc(sizeof(char) * length);
  
    // 複製第一個字串至新的陣列空間
    strcpy(result, str1);
    // 串接第二個字串至新的陣列空間
    strcat(result, str2);
  
    return result;
}
