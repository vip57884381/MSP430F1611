//**************************************//
//  實驗: 7SEG
//  腳位: OUT P6.0 、P6.1 、P6.2 、P6.3 、P6.4 、P6.5 、P6.6 、P6.7
//            X2D2 、X2D3 、X2D4 、X2D5 、X2D6 、X2D7 、X2D8 、X2D9
//  實驗結果: 7段顯示器上顯示 字母0~F,(-),(.)
//  注意事項: 共陽型七段顯示器
//**************************************//
#include "../../main.h"

UINT8 _7segTable[]={0x3f,0x06,0x5b,0x4f,0x66, //數字0～4
                   0x6d,0x7d,0x07,0x7f,0x6f, //數字5～9
                   0x77,0x7c,0x39,0x5e,0x79, //數字A,b,C,d,E
                   0x71,0x40,0x80};          //字母F,負號(-),小數點(.)
UINT8 _7segTable_length = sizeof(_7segTable)/sizeof(*_7segTable); // 取得 _7segTable 大小

void _7SEG_initIO()
{
  P6DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 dir output
  P6OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 = 0
}

void _7SEG()
{
  UINT8 i; // 迴圈變數
  for(i=0 ; i<_7segTable_length ; i++)
  {
    P6OUT = ~_7segTable[i];   // 取出table陣列值
    wait(250);               // delay 250ms
  }
}
