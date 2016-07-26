#define LCD_EN_HIGH P3OUT |= BIT2			// 定義 LCD_EN_HIGH
#define LCD_EN_LOW  P3OUT &= ~BIT2			// 定義 LCD_EN_LOW
#define LCD_RW_HIGH P3OUT |= BIT1			// 定義 LCD_RW_HIGH
#define LCD_RW_LOW  P3OUT &= ~BIT1			// 定義 LCD_RW_LOW
#define LCD_RS_HIGH P3OUT |= BIT0			// 定義 LCD_RS_HIGH
#define LCD_RS_LOW  P3OUT &= ~BIT0			// 定義 LCD_RS_LOW

void LCD_initIO();							// 初始化 LCD 腳位
void LCD_init();							// LCM啟始
void LCD_writeInst(UINT8 comm);				// 寫入指令到LCD
void LCD_checkBF();							// 檢查忙碌函數
void LCD_writeChar(UINT8 data);				// 寫入資料到LCM
void LCD_writeString(UINT8 col, UINT8 count, char table[]);	// 寫入字串到LCD函數開始
void LCD_transStr(char *in , char *out) ;
char *string_concat(char *str1, char *str2) ;
