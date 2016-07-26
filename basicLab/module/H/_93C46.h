#define CS_93C46_LOW  P5OUT &= ~BIT4
#define CS_93C46_HIGH P5OUT |= BIT4
#define CK_93C46_LOW  P5OUT &= ~BIT5
#define CK_93C46_HIGH P5OUT |= BIT5
#define DI_93C46_LOW  P5OUT &= ~BIT6
#define DI_93C46_HIGH P5OUT |= BIT6
#define DO_93C46_LOW  ~(P5IN & BIT7)
#define DO_93C46_HIGH P5IN & BIT7

void _93C46_initIO();
void clock93C46();
void EWEN();// 致能EEPROM寫入及清除
void EWDS();// EEPROM清除全部記憶體
void ERAL();// 禁能EEPROM寫入及清除
void send93C46(UINT8 Addr);// 送入93C46串列EEPROM資料
void write93C46(UINT8 Addr, UINT8 ch);// 寫入93C46串列EEPROM資料
UINT8 read93C46(UINT8 Addr);// 讀取93C46串列EEPROM資料
