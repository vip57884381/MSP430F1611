//**************************************//
//  實驗: _4_7SEG
//  腳位: OUT P6.0 、P6.1 、P6.2 、P6.3 、P6.4 、P6.5 、P6.6 、P6.7
//            X2D2 、X2D3 、X2D4 、X2D5 、X2D6 、X2D7 、X2D8 、X2D9
//        OUT P1.1 、P1.2 、P1.3 、P1.4
//            X2D0 、X2D1 、X2D10、X2D11
//**************************************//
#include "../../main.h"

UINT8 _4_7segTable[]={0x3f,0x06,0x5b,0x4f,0x66, //數字0～4
                   0x6d,0x7d,0x07,0x7f,0x6f, //數字5～9
                   0x77,0x7c,0x39,0x5e,0x79, //數字A,b,C,d,E
                   0x71,0x40,0x80};          //字母F,負號(-),小數點(.)
UINT8 scan[4]={0x10,0x08,0x04,0x02};       // 掃瞄行數P1.4 、P1.3 、P1.2 、P1.1
UINT8 cnt = 0;                             // 4_7SEG 掃描位數

void _4_7SEG_initIO()
{
  P1DIR |= (BIT1 + BIT2+ BIT3+ BIT4);
  P1OUT &= ~(BIT1 + BIT2+ BIT3+ BIT4);
  P6DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 dir output
  P6OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 = 0
}

void _4_7SEG(UINT8 i)
{
  P1OUT = ~scan[cnt]; // 掃瞄，取出 scan 陣列值，並反向
  P6OUT = _4_7segTable[i]; // 顯示，取出 _7segTable 陣列值
  (cnt==3) ? cnt = 0 : cnt++ ; // 掃描位數移動(千 ->百 ->十 ->個)
  wait(1);
}
