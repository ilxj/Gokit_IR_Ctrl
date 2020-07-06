#include "Hal_PIR/Hal_PIR_Rec.h"
#include "Hal_PIR/Hal_PIR.h"


void EXTIx_Init(GPIO_TypeDef* GPIOx ,uint16_t GPIO_Pin_x,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    uint32_t EXTI_Line_x;
    uint8_t GPIO_PinSource_x;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

        switch (GPIO_Pin_x)
        {
            case GPIO_Pin_0:
                        EXTI_Line_x = EXTI_Line0;
                        GPIO_PinSource_x = GPIO_PinSource0;
                        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
                break;
            case GPIO_Pin_1:
                        EXTI_Line_x = EXTI_Line1;
                        GPIO_PinSource_x = GPIO_PinSource1;
                        NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
                break;
            case GPIO_Pin_2:
                EXTI_Line_x = EXTI_Line2;
                GPIO_PinSource_x = GPIO_PinSource2;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
                break;
            case GPIO_Pin_3:
                EXTI_Line_x = EXTI_Line3;
                GPIO_PinSource_x = GPIO_PinSource3;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
                break;
            case GPIO_Pin_4:
                EXTI_Line_x = EXTI_Line4;
                GPIO_PinSource_x = GPIO_PinSource4;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
                break;
            case GPIO_Pin_5:
                EXTI_Line_x = EXTI_Line5;
                GPIO_PinSource_x = GPIO_PinSource5;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                break;
            case GPIO_Pin_6:
                EXTI_Line_x = EXTI_Line6;
                GPIO_PinSource_x = GPIO_PinSource6;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                break;
            case GPIO_Pin_7:
                EXTI_Line_x = EXTI_Line7;
                GPIO_PinSource_x = GPIO_PinSource7;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                break;
            case GPIO_Pin_8:
                EXTI_Line_x = EXTI_Line8;
                GPIO_PinSource_x = GPIO_PinSource8;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                break;
            case GPIO_Pin_9:
                EXTI_Line_x = EXTI_Line9;
                GPIO_PinSource_x = GPIO_PinSource9;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                break;
            case GPIO_Pin_10:
                EXTI_Line_x = EXTI_Line10;
                GPIO_PinSource_x = GPIO_PinSource10;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;
            case GPIO_Pin_11:
                EXTI_Line_x = EXTI_Line11;
                GPIO_PinSource_x = GPIO_PinSource11;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;
            case GPIO_Pin_12:
                EXTI_Line_x = EXTI_Line12;
                GPIO_PinSource_x = GPIO_PinSource12;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;
            case GPIO_Pin_13:
                EXTI_Line_x = EXTI_Line13;
                GPIO_PinSource_x = GPIO_PinSource13;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;
            case GPIO_Pin_14:
                EXTI_Line_x = EXTI_Line14;
                GPIO_PinSource_x = GPIO_PinSource14;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;
            case GPIO_Pin_15:
                EXTI_Line_x = EXTI_Line15;
                GPIO_PinSource_x = GPIO_PinSource15;
                NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                break;


            default:
                break;
        }

        if (GPIOx == GPIOA)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOB)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOC)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOD)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOF)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource_x);

        }
        if (GPIOx == GPIOG)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTA,PORTEʱ��
            GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOG, &GPIO_InitStructure);
            EXTI_ClearFlag(EXTI_Line_x);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource_x);

        }

            EXTI_InitStructure.EXTI_Line=EXTI_Line_x;
            EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            EXTI_InitStructure.EXTI_LineCmd = ENABLE;
            EXTI_Init(&EXTI_InitStructure);        //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;// /抢占优先级2，
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;              // //子优先级3
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                          //使能外部中断通道
            NVIC_Init(&NVIC_InitStructure);

}

uint32_t Pir_TimeCount = 0;
uint32_t Pir_TimeCount_flag = 0;
uint32_t Pir_RecFlag = 0;

void Hal_PirRec_Init(void)
{
    EXTIx_Init(GPIO_PIR_Rec_PORT,GPIO_PIR_Rec_PIN,2,1);
}

extern uint32_t SystemTimeCount;
static uint32_t lowCnt          = 0;
uint32_t Pir_NegativeTable[128];
uint32_t Pir_PositiveTable[128];
uint32_t PirTable[2][FALLING_CNT];

void get_IrCode( void )
{
    if(Pir_RecFlag == 1)
    {
        int32_t Falling_EdgesCnt            = FALLING_CNT;//1次按键有114个下降沿
        int32_t firstNegativePulseTime      = 250;//第一次低电平有效时长，用于过滤
        Pir_RecFlag = 0;

        if(ReadPirSta()==0)
        {
                int32_t  i = 0;
                for ( i = 0; i < Falling_EdgesCnt; i++)
                {
                    Pir_TimeCount = 0;
                    while(ReadPirSta() == 0);
                    if( i==0&&Pir_TimeCount<firstNegativePulseTime )
                    {
                        printf("Invaild IR pulse :%d .\r\n",Pir_TimeCount );
                        break;
                    }
                    PirTable[0][i] = Pir_TimeCount;
                    if( i==Falling_EdgesCnt-1 )
                    {
                        printf("capture complete Cnt:%d.\r\n",i+1 );
                        break;
                    }
                    Pir_TimeCount = 0;
                    while(ReadPirSta() == 1);
                    PirTable[1][i] = Pir_TimeCount;
                }

                if( i>=Falling_EdgesCnt-1 )
                {
                    printf("PirTable :\r\n");
                    for ( i = 0; i < Falling_EdgesCnt; i++)
                    {
                        if( i!=0 && i%10==0 )
                        {
                            printf("\r\n");
                        }
                        printf("%d, ",PirTable[0][i] );
                        printf("%d, ",PirTable[1][i] );
                    }
                }
            }
    }
}
