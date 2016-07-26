//**************************************//
//  實驗: TimerA
//  實驗結果: 使用TimerA做延遲效果
//**************************************//
#include "../../main.h"

UINT8 timerFlag ;

void wait(unsigned int mSec)
{
  UINT16 i;
  for(i = 0 ; i < mSec ; i++)
    SetTimer();
}

void SetTimer() // 1ms
{
  timerFlag = 1 ;
  // 秒 = (1/32768) * (TACCR0 + 1)
  TACTL = TASSEL_1 + TACLR + ID_0 + MC_1;
  TACCR0 = 32;
  TACCTL0 |= CCIE;
  _EINT() ;
  while(timerFlag);
}

#pragma vector=TIMERA0_VECTOR
__interrupt void delay(void)
{
   TACTL ^= MC_1;
   timerFlag = 0 ;
}
