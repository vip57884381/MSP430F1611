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
void EWEN();// �P��EEPROM�g�J�βM��
void EWDS();// EEPROM�M�������O����
void ERAL();// �T��EEPROM�g�J�βM��
void send93C46(UINT8 Addr);// �e�J93C46��CEEPROM���
void write93C46(UINT8 Addr, UINT8 ch);// �g�J93C46��CEEPROM���
UINT8 read93C46(UINT8 Addr);// Ū��93C46��CEEPROM���
