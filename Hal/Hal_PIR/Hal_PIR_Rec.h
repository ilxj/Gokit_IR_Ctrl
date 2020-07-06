/********************************************************
* @file      Hal_PIR_Rec.h
* @author    yinerda
* @version   V1.0
* @date      2015-07-06
*
* @brief     www.yinerda.com
*
*********************************************************/

#ifndef _HAL_PIR_REC_H
#define _HAL_PIR_REC_H

#include "stm32f10x.h"
#include "delay.h"
#include "Hal_Usart/hal_uart.h"
#include "Hal_PIR/hal_PIR.h"


#define GPIO_PIR_Rec_CLK    RCC_APB2Periph_GPIOA
#define GPIO_PIR_Rec_PORT   GPIOA
#define GPIO_PIR_Rec_PIN    GPIO_Pin_4

#define  ReadPirSta()  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)


void Hal_PirRec_Init(void);
uint16_t PirCountTimeLSB(void);
uint16_t PirCountTimeMSB(void);

void Pir_Handle(void);
void get_IrCode( void );

#endif /*_HAL_PIR_REC_H*/

