#define LCD_EN_HIGH P3OUT |= BIT2			// �w�q LCD_EN_HIGH
#define LCD_EN_LOW  P3OUT &= ~BIT2			// �w�q LCD_EN_LOW
#define LCD_RW_HIGH P3OUT |= BIT1			// �w�q LCD_RW_HIGH
#define LCD_RW_LOW  P3OUT &= ~BIT1			// �w�q LCD_RW_LOW
#define LCD_RS_HIGH P3OUT |= BIT0			// �w�q LCD_RS_HIGH
#define LCD_RS_LOW  P3OUT &= ~BIT0			// �w�q LCD_RS_LOW

void LCD_initIO();							// ��l�� LCD �}��
void LCD_init();							// LCM�ҩl
void LCD_writeInst(UINT8 comm);				// �g�J���O��LCD
void LCD_checkBF();							// �ˬd���L���
void LCD_writeChar(UINT8 data);				// �g�J��ƨ�LCM
void LCD_writeString(UINT8 col, UINT8 count, char table[]);	// �g�J�r���LCD��ƶ}�l
void LCD_transStr(char *in , char *out) ;
char *string_concat(char *str1, char *str2) ;
