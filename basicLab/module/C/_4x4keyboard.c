#include "../../main.h"

char rowkey = 0;	// 那一列被按下
char col ,row;		// col:行  row：列
int tmp[4]={0,0,0,0};

void _4x4keyboard_initIO()
{
  P2DIR |= (BIT2 + BIT3 + BIT4 + BIT5);    // P2.2~2.5 output
  P2OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5);
  P2IE |= ~(BIT2 + BIT3 + BIT4 + BIT5);    // P2.2~2.5 input 開啟中斷智能
  P2IES &= ~(BIT2 + BIT3 + BIT4 + BIT5);;
}

int getKeyVal(int i) {
	return tmp[i];
}

void scanner() //鍵盤掃瞄
{
	UINT8 scan[4]={0x04,0x08,0x10,0x20};       //掃瞄行數
	P2OUT = scan[col] ;       // 行送出掃瞄信號
	wait(1);                  // 延遲 1ms
	(col==3) ? col = 0 : col++ ; 
}

#pragma vector=PORT2_VECTOR
__interrupt   void scannerReceive(void) { 
	rowkey = ((P2IN) & 0xc3); // 取出列資料
	switch(rowkey & 0xc3)   // 取出 R0~R4 哪個被按下
	{
		case 0x01:            // R0 被按下
			row = 0;            // row = 0
			break;
		case 0x02:            // R1 被按下
			row = 1;            // row = 1
			break;
		case 0x40:            // R2 被按下
			row = 2;            // row = 2
			break;
		case 0x80:            // R3 被按下
			row = 3;            // row = 3
			break;
		default:
			row = 99;
	}
	if (row < 99)
	{
		rowkey = 4 * col + row ; //計算鍵盤值
		if(rowkey != tmp[3])
		{
      		tmp[0] = tmp[1];
      		tmp[1] = tmp[2];
      		tmp[2] = tmp[3];
      		tmp[3] = rowkey;
      	}
	}
  P2IFG=0x00;        // 清除中斷暫存器的值
}
