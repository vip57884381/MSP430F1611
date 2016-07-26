//**************************************//
//  ����: 7SEG
//  �}��: OUT P6.0 �BP6.1 �BP6.2 �BP6.3 �BP6.4 �BP6.5 �BP6.6 �BP6.7
//            X2D2 �BX2D3 �BX2D4 �BX2D5 �BX2D6 �BX2D7 �BX2D8 �BX2D9
//  ���絲�G: 7�q��ܾ��W��� �r��0~F,(-),(.)
//  �`�N�ƶ�: �@�����C�q��ܾ�
//**************************************//
#include "../../main.h"

UINT8 _7segTable[]={0x3f,0x06,0x5b,0x4f,0x66, //�Ʀr0��4
                   0x6d,0x7d,0x07,0x7f,0x6f, //�Ʀr5��9
                   0x77,0x7c,0x39,0x5e,0x79, //�ƦrA,b,C,d,E
                   0x71,0x40,0x80};          //�r��F,�t��(-),�p���I(.)
UINT8 _7segTable_length = sizeof(_7segTable)/sizeof(*_7segTable); // ���o _7segTable �j�p

void _7SEG_initIO()
{
  P6DIR |= (BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 dir output
  P6OUT &= ~(BIT0 +BIT1 + BIT2+ BIT3+ BIT4+ BIT5+ BIT6+ BIT7);			// P6 = 0
}

void _7SEG()
{
  UINT8 i; // �j���ܼ�
  for(i=0 ; i<_7segTable_length ; i++)
  {
    P6OUT = ~_7segTable[i];   // ���Xtable�}�C��
    wait(250);               // delay 250ms
  }
}
