#ifndef __TM1637_H
#define __TM1637_H	
#include "stm32f1xx_hal.h"


//------------------------------------------------------------移植修改区-----------------------------------------------------------------------


#define    TM_DIO_PORT    	GPIOA
#define    TM_DIO_CLK 	   HAL_GPIO_ReadPin(TM_DIO_PORT,TM_DIO_PIN)		
#define    TM_DIO_PIN			GPIO_PIN_8			        

#define    TM_CLK_PORT    	GPIOA
#define    TM_CLK_CLK 	    HAL_GPIO_ReadPin(TM_CLK_PORT,TM_CLK_PIN)		
#define    TM_CLK_PIN		  GPIO_PIN_9
		

//时钟线和数据线高低电平的宏定义，不需修改
#define      CLK_1         HAL_GPIO_WritePin(TM_CLK_PORT,TM_CLK_PIN,GPIO_PIN_SET)
#define      CLK_0        HAL_GPIO_WritePin(TM_CLK_PORT,TM_CLK_PIN,GPIO_PIN_RESET)
#define      DIO_1         HAL_GPIO_WritePin(TM_DIO_PORT,TM_DIO_PIN,GPIO_PIN_SET)
#define      DIO_0         HAL_GPIO_WritePin(TM_DIO_PORT,TM_DIO_PIN,GPIO_PIN_RESET)

//相关函数声明
void GPIO_Config(void);

void TM1637_WriteBit(unsigned char mBit);
void TM1637_WriteByte(unsigned char Byte);


//I2C开始
void TM1637_start(void);

//I2C应答
void TM1637_ack(void);

//I2C结束ֹ
void TM1637_stop(void);
	
//写数据函数
void TM1637_Write(unsigned char DATA);

//按照0~9顺序显示
void TM1637_display(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t h);

 
#endif 
