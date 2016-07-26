//**************************************//
//  實驗: DAC
//  腳位: DAC
//             LSB                                             MSB
//        OUT P2.0、 P2.1 、P2.2 、P2.3 、P2.4 、P2.5 、P2.6 、P2.7
//            X2D26、X2D27、X2D28、X2D29、X2D30、X2D31、X2D32、X2D33
//  注意事項: 1. 本實驗需把 LCD 拆下來
//            2. 如果 DAC_Vo > 3.3V，請重新上電
//**************************************//

#include "../../main.h"

void DAC08_initIO() {
  P2DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);	// P2 dir output
  P2OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);	// P2 = 0
}

void DAC08_setValue(UINT8 output) {
  P2OUT = ~output ;	// DAC output
  wait(100) ;		// delay 100ms
}

char* decToBin(UINT8 input) {
	char *result = (char*)malloc(sizeof(char) * 16);
	UINT8 tmpIn;
	int i;
	tmpIn = input;
	for(i = 16 ; i > 8 ; i--)
	{
		if((tmpIn % 2) == 0)
			result[i] = '0';
		else
			result[i] = '1';
		
		if(tmpIn > 0)
			tmpIn = tmpIn / 2;
	}
	result[0] = 'D';
	result[1] = 'A';
	result[2] = 'C';
	result[3] = ' ';
	result[4] = ' ';
	result[5] = ' ';
	result[6] = ' ';
	result[7] = '=';
	return result;
}

char* numToStr(UINT8 input) {
	char *result = (char*)malloc(sizeof(char) * 16);
	int tmpIn;
	tmpIn = input * 12;
	result[0] = 'D';
	result[1] = 'A';
	result[2] = 'C';
	result[3] = ' ';
	result[4] = ' ';
	result[5] = ' ';
	result[6] = ' ';
	result[7] = '=';
	result[8] = ' ';
	result[9] = tmpIn/1000 + '0';
	result[10] = '.';
	result[11] = (tmpIn/100)%10 + '0';
	result[12] = (tmpIn/10)%10 + '0';
	result[13] = tmpIn%10 + '0';
	result[14] = 'V';
	result[15] = ' ';
	return result;
}
