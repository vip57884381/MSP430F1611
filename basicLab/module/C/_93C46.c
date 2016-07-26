//**************************************//
//  ����: SPI
//  �}��: SPI
//        OUT P5.4(CS)�BP5.5(CK)�BP5.6(DI)
//            X2D36   �BX2D37   �BX2D38
//        IN  P5.7(DO)
//            X2D39
//**************************************//
#include "../../main.h"

void _93C46_initIO() {
  P5DIR |= (BIT4 + BIT5 + BIT6);
  P5OUT &= ~(BIT4 + BIT5 + BIT6);
  DI_93C46_HIGH;
  DO_93C46_HIGH;
  CS_93C46_LOW;
  CK_93C46_LOW;
}

void clock93C46() {
	CK_93C46_HIGH; // SK=1;
	wait(1); // ����1ms
	CK_93C46_LOW; // SK=0;
	wait(1); // ����1ms
}

void EWEN() // EEPROM�g�J�βM���P��
{
	CS_93C46_HIGH; // CS=1; �}��EEPROM����
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x60); // �e�J�ާ@�X0�Ϋ��O�A�P��ٰ�/�g�J�ʧ@
	CS_93C46_LOW; // CS=0; ����EEPROM����
	wait(1); // ����1ms
}

void EWDS() // EEPROM�g�J�βM���T��
{
	CS_93C46_HIGH; // CS=1; �}��EEPROM����
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x00); // �e�J�ާ@�X0�Ϋ��O�A�T��ٰ�/�g�J�ʧ@
	CS_93C46_LOW; // CS=0; ����EEPROM����
	wait(1); // ����1ms
}

void ERAL() // EEPROM�M�������O����
{
	CS_93C46_HIGH; // CS=1; �}��EEPROM����
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x00 + 0x40); // �e�J�ާ@�X0�Ϋ��O�A�T��ٰ�/�g�J�ʧ@
	CS_93C46_LOW; // CS=0; ����EEPROM����
	wait(1); // ����1ms
}

void send93C46(UINT8 Addr) // �e�J93C46��CEEPROM���
{
	UINT8 i = 0;
	for (i = 0; i < 8; i++) // �e�J8-bit
	{
		if (Addr & 0x80) // �Ybit7=1�A
			DI_93C46_HIGH; // �hDI=1
		else
			// �Ybit7=0�A
			DI_93C46_LOW; // �hDI=0
		clock93C46(); // ��C�ɯߡAbit�e�JEEPROM
		Addr <<= 1; // ��}����
	}
}

void write93C46(UINT8 Addr, UINT8 ch)// �g�J93C46��CEEPROM���
{
	CS_93C46_HIGH; // CS=1; �}��EEPROM����
	DI_93C46_HIGH; // DI=1;
	clock93C46(); // clock93C46
	DI_93C46_LOW; // DI=0;
	clock93C46(); // clock93C46
	send93C46(0x80 + Addr); // �e�J�ާ@�X1�Φ�}
	send93C46(ch); // �g�J���
	CS_93C46_LOW; // CS=0; ����EEPROM����
}

UINT8 read93C46(UINT8 Addr)// Ū��93C46��CEEPROM���
{
	UINT8 ch = 0;
	UINT8 i = 0;

	CS_93C46_HIGH;// CS=1; �}��EEPROM����
	DI_93C46_HIGH;// DI=1;
	clock93C46();// clock
	DI_93C46_HIGH;// DI=1;
	clock93C46();// clock
	send93C46(0x00 + Addr); // �e�J�ާ@�X0�Φ�}
	for (i = 0; i < 8; i++) // Ū��8bit��ch
			{
		clock93C46(); // clock
		ch = ch << 1; // ��}����
		if (DO_93C46_HIGH) // �Y DO = 1�A
			ch = ch | 0x01; // ch = 1
	}
	CS_93C46_LOW; // CS=0; ����EEPROM����
	return ch; // �N8-bit��ưe�^�D�{��
}
