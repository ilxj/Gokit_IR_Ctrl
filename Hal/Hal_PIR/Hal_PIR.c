/**
********************************************************
*
* @file      hal_PIR.c
* @author    yinerda
* @version   V1.0
* @date      2015-07-06
*
* @brief     www.yinerda.com
*
*********************************************************/

#include "Hal_PIR/hal_PIR.h"


/*
 * ��������TIM3_GPIO_Config
 * ����  ������TIM3�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);

  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void TIME2_GPIO_PWM(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void TIME2_GPIO_L(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}
/*******************************************************************************
* Function Name  : TIM3_Int_Init
* Description    : TIM3 initialization function
* Input          : arr ��װ��ֵ
                                     psc Ԥ��Ƶ
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void TIM2_Int_Init(u16 arr,u16 psc)
{
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        TIM_DeInit(TIM2);
        TIM_TimeBaseStructure.TIM_Period = arr;
        TIM_TimeBaseStructure.TIM_Prescaler = psc;
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;

        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}


/*
 * ��������TIM3_Mode_Config
 * ����  ������TIM3�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_Mode_Config(void)
{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* PWM�źŵ�ƽ����ֵ */
    u16 CCR1_Val = 625;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
  /* TIM3 enable counter */
  TIM_Cmd(TIM2, DISABLE);                   //ʹ�ܶ�ʱ��3



}

void TIM2_IRQHandler(void)
{
         if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
         {
                TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
         }
}

void Pir_Init(void)
{
    TIM2_GPIO_Config();
    TIM2_Int_Init(1879,0);
    TIM2_Mode_Config();
}

void PirSend( uint32_t Buf[FALLING_CNT*2] )
{
    int32_t i         = 0;
    int32_t reSendCnt = 3; //重发3次，确保收到
    printf("Send Start\r\n");
    do{
        for( i=0;i<FALLING_CNT*2;i++ )
        {
            //低电平
            if( i&0x01 )
            {
                PIR_PIN_H();
            }
            else//高电平
            {
                PIR_PIN_L();
            }
            if( Buf[i]*10>0 )
            {
                Delay_us(Buf[i]*10);
            }
        }
        reSendCnt--;
    }while ( reSendCnt>0 );
    printf("Send OK\r\n");
}


