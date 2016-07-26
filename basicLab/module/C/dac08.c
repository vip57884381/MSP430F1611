//**************************************//
//  ����: DAC
//  �}��: DAC
//             LSB                                             MSB
//        OUT P2.0�B P2.1 �BP2.2 �BP2.3 �BP2.4 �BP2.5 �BP2.6 �BP2.7
//            X2D26�BX2D27�BX2D28�BX2D29�BX2D30�BX2D31�BX2D32�BX2D33
//  �`�N�ƶ�: 1. ������ݧ� LCD ��U��
//            2. �p�G DAC_Vo > 3.3V�A�Э��s�W�q
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
