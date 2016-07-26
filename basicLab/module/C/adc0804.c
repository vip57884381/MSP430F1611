//**************************************//
//  實驗: ADC
//  腳位: ADC
//        OUT P1.6(RD)、P1.5(WR)
//            X2D25   、X2D24
//        IN  P1.7
//            X2D34
//        IN  P2.0 、P2.1 、P2.2 、P2.3 、P2.4 、P2.5 、P2.6 、P2.7
//            X2D26、X2D27、X2D28、X2D29、X2D30、X2D31、X2D32、X2D33
//**************************************//

#include "../../main.h"

void ADC0804_initIO() {
  P1DIR |= (BIT5 + BIT6);
  P1OUT &= ~(BIT5 + BIT6);
}

UINT8 ADC0804_getValue() {
  UINT8 adc;
  WR_ADC0804_LOW;             // 開始轉換
  WR_ADC0804_HIGH;            // 寫入時序
  while (!INTR_ADC0804_LOW);  // 等待轉換完畢
  RD_ADC0804_LOW;             // 讀取時序
  adc = P2IN;                 // 讀取 A/D 轉換值
  RD_ADC0804_HIGH;
  return adc;
}

