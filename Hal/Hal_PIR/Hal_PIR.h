/********************************************************
* @file      _HAL_PIR_H
* @author    yinerda
* @version   V1.0
* @date      2015-07-06
*
* @brief     www.yinerda.com
*
*********************************************************/

#ifndef _HAL_PIR_H
#define _HAL_PIR_H

#include "stm32f10x.h"
#include "delay.h"


#define FALLING_CNT         114 //下降沿的个数
#define SWITCH_ON           0
#define SWITCH_OFF          1
#define TEMP_16             2
#define TEMP_17             3
#define TEMP_18             4
#define TEMP_19             5
#define TEMP_20             6
#define TEMP_21             7
#define TEMP_22             8
#define TEMP_23             9
#define TEMP_24             10
#define TEMP_25             11
#define TEMP_26             12
#define TEMP_27             13
//#define GPIO_PIR_CLK    RCC_APB2Periph_GPIOA
//#define GPIO_PIR_PORT   GPIOA
//#define GPIO_PIR_PIN    GPIO_Pin_0


//#define PIR_PIN_H()  TIME2_GPIO_PWM();TIM_Cmd(TIM2, ENABLE);//TIM_SelectOCxM(TIM2, TIM_Channel_1, TIM_OCMode_PWM1);
//

//#define PIR_PIN_L()  TIME2_GPIO_L();TIM_Cmd(TIM2, DISABLE);

#define PIR_PIN_L()  TIME2_GPIO_PWM();TIM_Cmd(TIM2, ENABLE);//TIM_SelectOCxM(TIM2, TIM_Channel_1, TIM_OCMode_PWM1);


#define PIR_PIN_H()  TIME2_GPIO_L();TIM_Cmd(TIM2, DISABLE);

//#define PIR_PIN_H()  TIM_Cmd(TIM2, ENABLE);
//#define PIR_PIN_L()  TIM_Cmd(TIM2, DISABLE);


void Pir_Init(void);
void PirSend( uint32_t Buf[FALLING_CNT*2] );
void TIME2_GPIO_PWM(void);
void TIME2_GPIO_L(void);
#endif /*_HAL_PIR_H*/


