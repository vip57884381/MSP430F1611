//**************************************//
//  ����: ADC
//  �}��: ADC
//        OUT P1.6(RD)�BP1.5(WR)
//            X2D25   �BX2D24
//        IN  P1.7
//            X2D34
//        IN  P2.0 �BP2.1 �BP2.2 �BP2.3 �BP2.4 �BP2.5 �BP2.6 �BP2.7
//            X2D26�BX2D27�BX2D28�BX2D29�BX2D30�BX2D31�BX2D32�BX2D33
//**************************************//

#include "../../main.h"

void ADC0804_initIO() {
  P1DIR |= (BIT5 + BIT6);
  P1OUT &= ~(BIT5 + BIT6);
}

UINT8 ADC0804_getValue() {
  UINT8 adc;
  WR_ADC0804_LOW;             // �}�l�ഫ
  WR_ADC0804_HIGH;            // �g�J�ɧ�
  while (!INTR_ADC0804_LOW);  // �����ഫ����
  RD_ADC0804_LOW;             // Ū���ɧ�
  adc = P2IN;                 // Ū�� A/D �ഫ��
  RD_ADC0804_HIGH;
  return adc;
}

