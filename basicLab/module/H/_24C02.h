#define SDA BIT6
#define SCL BIT5
#define SDA_HIGH P1OUT |= SDA
#define SCL_HIGH P1OUT |= SCL
#define SDA_LOW P1OUT &= ~(SDA)
#define SCL_LOW P1OUT &= ~(SCL)

#define	writeDeviceAdr 0xA0 
#define	readDeviceAdr 0xA1

void _24C02_initIO();
void start();
void stop();
void writeAck();
void noAck();
UINT8 readAck();
void write8Bit(UINT8 input);
void write24c02(char *wData,UINT8 romAdr,UINT8 bit);
char read8Bit();
void read24c02(char *rData,UINT8 romAdr,UINT8 bit);
