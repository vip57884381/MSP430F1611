//**************************************//
//  ����: _4_7SEG
//  �}��: OUT P6.0 �BP6.1 �BP6.2 �BP6.3 �BP6.4 �BP6.5 �BP6.6 �BP6.7
//            X2D2 �BX2D3 �BX2D4 �BX2D5 �BX2D6 �BX2D7 �BX2D8 �BX2D9
//        OUT P1.1 �BP1.2 �BP1.3 �BP1.4
//            X2D0 �BX2D1 �BX2D10�BX2D11
//**************************************//
#include "../../main.h"

UINT8 _4_7segTable[]={0x3f,0x06,0x5b,0x4f,0x66, //�Ʀr0��4
                   0x6d,0x7d,0x07,0x7f,0x6f, //�Ʀr5��9
                   0x77,0x7c,0x39,0x5e,0x79, //�ƦrA,b,C,d,E
                   0x71,0x40,0x80};          //�r��F,�t��(-),�p���I(.)
UINT8 scan[4]={0x10,0x08,0x04,0x02};       // ���˦��P1.4 �BP1.3 �BP1.2 �BP1.1
UINT8 cnt = 0;                             // 4_7SEG ���y���

void _4_7SEG_initIO()
{
  P1DIR |= (BIT1 + BIT2+ BIT3+ BIT4);
  P1OUT &= ~(BIT1 + BIT2+ BIT3+ BIT4);
  P6DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 dir output
  P6OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 = 0
}

void _4_7SEG(UINT8 i)
{
  P1OUT = ~scan[cnt]; // ���ˡA���X scan �}�C�ȡA�äϦV
  P6OUT = _4_7segTable[i]; // ��ܡA���X _7segTable �}�C��
  (cnt==3) ? cnt = 0 : cnt++ ; // ���y��Ʋ���(�d ->�� ->�Q ->��)
  wait(1);
}
