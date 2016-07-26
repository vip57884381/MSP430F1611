#include "../../main.h"

char rowkey = 0;	// ���@�C�Q���U
char col ,row;		// col:��  row�G�C
int tmp[4]={0,0,0,0};

void _4x4keyboard_initIO()
{
  P2DIR |= (BIT2 + BIT3 + BIT4 + BIT5);    // P2.2~2.5 output
  P2OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5);
  P2IE |= ~(BIT2 + BIT3 + BIT4 + BIT5);    // P2.2~2.5 input �}�Ҥ��_����
  P2IES &= ~(BIT2 + BIT3 + BIT4 + BIT5);;
}

int getKeyVal(int i) {
	return tmp[i];
}

void scanner() //��L����
{
	UINT8 scan[4]={0x04,0x08,0x10,0x20};       //���˦��
	P2OUT = scan[col] ;       // ��e�X���˫H��
	wait(1);                  // ���� 1ms
	(col==3) ? col = 0 : col++ ; 
}

#pragma vector=PORT2_VECTOR
__interrupt   void scannerReceive(void) { 
	rowkey = ((P2IN) & 0xc3); // ���X�C���
	switch(rowkey & 0xc3)   // ���X R0~R4 ���ӳQ���U
	{
		case 0x01:            // R0 �Q���U
			row = 0;            // row = 0
			break;
		case 0x02:            // R1 �Q���U
			row = 1;            // row = 1
			break;
		case 0x40:            // R2 �Q���U
			row = 2;            // row = 2
			break;
		case 0x80:            // R3 �Q���U
			row = 3;            // row = 3
			break;
		default:
			row = 99;
	}
	if (row < 99)
	{
		rowkey = 4 * col + row ; //�p����L��
		if(rowkey != tmp[3])
		{
      		tmp[0] = tmp[1];
      		tmp[1] = tmp[2];
      		tmp[2] = tmp[3];
      		tmp[3] = rowkey;
      	}
	}
  P2IFG=0x00;        // �M�����_�Ȧs������
}
