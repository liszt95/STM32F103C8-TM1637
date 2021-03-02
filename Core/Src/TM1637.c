#include "TM1637.h"


unsigned char tab[] =
{
	0x3F,/*0*/
	0x06,/*1*/
	0x5B,/*2*/
	0x4F,/*3*/
	0x66,/*4*/
	0x6D,/*5*/
	0x7D,/*6*/
	0x07,/*7*/
	0x7F,/*8*/
	0x6F,/*9*/
	0x77,/*10 A*/
	0x7C,/*11 b*/
	0x58,/*12 c*/
	0x5E,/*13 d*/
	0x79,/*14 E*/
	0x71,/*15 F*/
	0x76,/*16 H*/
	0x38,/*17 L*/
	0x54,/*18 n*/
	0x73,/*19 P*/
	0x3E,/*20 U*/
	0x00,/*21 ����*/
};


 /*
  *@breif GPIO_INIT  
  *@note  no
 */
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	/* GPIO_InitStructure.GPIO_Pin = TM_DIO_PIN | TM_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(TM_DIO_PORT,&GPIO_InitStructure);	*/
 
GPIO_InitStruct.Pin = TM_DIO_PIN | TM_CLK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void delay_us(uint16_t time)
{
uint16_t  i=0;
while(time--)
{
i=10;  
while(i--) ;
}
}

//дһ������λ
void TM1637_WriteBit(unsigned char mBit)
{
	CLK_0;
	delay_us(140);

	if(mBit)
		DIO_1;
	else
		DIO_0;
 
	delay_us(140);
	CLK_1;
	delay_us(140);	
}

//дһ���ֽ�    
void TM1637_WriteByte(unsigned char Byte)
{
	char loop = 0;
	for(loop = 0;loop<8;loop++)
	{
		TM1637_WriteBit((Byte>>loop) & 1);//��д��λ	
	}
	CLK_0;
	delay_us(140);
	DIO_1;	
	delay_us(140);
	CLK_1;		
	delay_us(140);
	while(HAL_GPIO_ReadPin(TM_DIO_PORT,TM_DIO_PIN) == 1);
	//�ȴ�Ӧ���ź�
}


 //��ʼ
void TM1637_start(void)
{
	 CLK_1;
	 DIO_1;
	 delay_us(2);
	 DIO_0;
}


//Ӧ��
void TM1637_ack(void)
{
	uint8_t i;
	CLK_0;
	delay_us(5);

	while(HAL_GPIO_ReadPin(TM_DIO_PORT,TM_DIO_PIN) == 0x01&&(i<250))
		i++;
	
	CLK_1;
	
	delay_us(2);
	
	CLK_0;
}

//IICֹͣ
void TM1637_stop(void)
{
	 CLK_0;
	 delay_us(2);
	 DIO_0;
	 delay_us(2);
	 CLK_1;
	 delay_us(2);
	 DIO_1;
	 delay_us(2);
}

//д���ݺ���
void TM1637_Write(unsigned char DATA)   
{
	unsigned char i;   
	for(i=0;i<8;i++)        
	{
		CLK_0;     
		if(DATA & 0x01)
			DIO_1;
		else 
			DIO_0;
		
		delay_us(3);
		
		DATA=DATA>>1;      
		CLK_1;
		
		delay_us(3);
	}
}


//��˳����ʾ
void TM1637_display(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t h)
{
	TM1637_start();
	TM1637_Write(0x40);//д����+�Զ���ַ��1+��ͨģʽ
	TM1637_ack();
	TM1637_stop();
	
	TM1637_start();
	
	TM1637_Write(0xc0);//������ʾ�׵�ַ����һ��LED
	TM1637_ack();
	
	TM1637_Write(tab[a]);
	TM1637_ack();
	
	TM1637_Write(tab[b]|h<<7);//hΪ1ʱ��ʾʱ���м������
	TM1637_ack();
	
	TM1637_Write(tab[c]);
	TM1637_ack();
	
	TM1637_Write(tab[d]);
	TM1637_ack();
	
	TM1637_stop();
	
	TM1637_start();
	TM1637_Write(0x8F);//����ʾ��0x89 2/16����  0x8F 14/16����
	TM1637_ack();
	TM1637_stop();
}
