//**************************************//
//  ����: LCD
//  �}��: OUT P3.2(EN)�BP3.1(RW)�BP3.0(RS)
//            X2D22   �BX2D13   �BX2D12
//        OUT P4.0 �BP4.1 �BP4.2 �BP4.3 �BP4.4 �BP4.5 �BP4.6 �BP4.7
//            X2D14�BX2D15�BX2D16�BX2D17�BX2D18�BX2D19�BX2D20�BX2D21
//  ���絲�G: LCD��� �Ĥ@�� 1234567890123456
//                   �ĤG�� ABCDEFGHIJKLMNOP
//**************************************//
#include "../../main.h"

void LCD_initIO() {
	P3DIR |= (BIT0+BIT1+BIT2);	// P3.0~3.2 dir output
	P4DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7); // P4 dir output
	P3OUT &= ~(BIT0+BIT1+BIT2);	// P3.0~3.2 = 0
	P4OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7); // P4 = 0
}

// LCM�ҩl
void LCD_init() {
	LCD_writeInst(0x30);
	LCD_writeInst(0x30);
	LCD_writeInst(0x30);
	LCD_writeInst(0x38); // 8bit�ǿ�A���2��A5X7�r��
	LCD_writeInst(0x08); // ��ܧ���Хk���A��в���T��
	LCD_writeInst(0x01); // �M�����
	LCD_writeInst(0x06); // ��ܧ���Хk���A��в���T��
	LCD_writeInst(0x0c); // �}����ܡA����ܴ�СA��Ф��{�{
}

// �g�J���O��LCD
void LCD_writeInst(UINT8 comm) {
	LCD_checkBF();
	P4OUT = comm;	//��}�e��BUS
	LCD_RS_LOW;
	LCD_RW_LOW;
	LCD_EN_HIGH;	//�g�J���O��LCD
	LCD_checkBF();
	LCD_EN_LOW;		//�T��LCD
}

// �ˬd���L���
void LCD_checkBF() {
	UINT8 tmp1;
	LCD_EN_LOW;		// �T��LCD
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

// �g�J��ƨ�LCM
void LCD_writeChar(UINT8 data) {
	LCD_checkBF();
	P4OUT = data; // ��ưe��BUS
	LCD_RS_HIGH;
	LCD_RW_LOW;
	LCD_EN_HIGH; //�g�J��ƨ�LCD
	LCD_checkBF();
	LCD_EN_LOW; // �T��LCD
}

// �g�J�r���LCD��ƶ}�l
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

/* string_concat [�r��ۥ[]
 * �N str1 �P str2 �ۥ[�A�ê�^�s���r��
 * */
char *string_concat(char *str1, char *str2) {
    // �p��һݪ��}�C����
    int length=strlen(str1)+strlen(str2)+1;
  
    // ���ͷs���}�C�Ŷ�
    char *result = (char*)malloc(sizeof(char) * length);
  
    // �ƻs�Ĥ@�Ӧr��ܷs���}�C�Ŷ�
    strcpy(result, str1);
    // �걵�ĤG�Ӧr��ܷs���}�C�Ŷ�
    strcat(result, str2);
  
    return result;
}
