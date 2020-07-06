#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>
#include <stdbool.h>
#include <stm32f10x.h>


#define SoftAp_Mode    0x01
#define AirLink_Mode   0x02

#define MAX_P0_LEN			128 	 		 //p0������󳤶�
#define MAX_PACKAGE_LEN		(MAX_P0_LEN*2) 	 //���ݻ�������󳤶�
#define MAX_RINGBUFFER_LEN	MAX_PACKAGE_LEN  //���λ�������󳤶�
#define Max_UartBuf         MAX_PACKAGE_LEN  //�������ݻ�������󳤶�


#define PROTOCOL_DEBUG //调试通信数据信息宏开关
#define DEBUG          //系统运行调试信息

#define Send_MaxTime   300
#define Send_MaxNum    2

#define		PRO_VER																"00000004"
#define		P0_VER																"00000004"
#define		HARD_VER															"02030100"
#define		SOFT_VER															"02030002"
#define		PRODUCT_KEY														    "6a7484ec6bc64f11bdf557ca38b8c65d"
#define     PRODUCT_SECRET                                                      "cf4776ebcd3d4e47ba8c233aae262bee"


__packed	typedef struct
{
    uint8_t             			Message_Buf[Max_UartBuf]; //���ڽ��ջ�����
    uint8_t             			Message_Len;	          //���ܵ������ݳ���
} UART_HandleTypeDef;

/*������*/
typedef enum
{
    Pro_W2D_GetDeviceInfo_Cmd 					= 0x01,
    Pro_D2W__GetDeviceInfo_Ack_Cmd				= 0x02,

    Pro_W2D_P0_Cmd 								= 0x03,
    Pro_D2W_P0_Ack_Cmd							= 0x04,

    Pro_D2W_P0_Cmd 								= 0x05,
    Pro_W2D_P0_Ack_Cmd							= 0x06,

    Pro_W2D_Heartbeat_Cmd 						= 0x07,
    Pro_D2W_heartbeatAck_Cmd					= 0x08,

    Pro_D2W_ControlWifi_Config_Cmd 				= 0x09,
    Pro_W2D_ControlWifi_Config_Ack_Cmd			= 0x0A,

    Pro_D2W_ResetWifi_Cmd 						= 0x0B,
    Pro_W2D_ResetWifi_Ack_Cmd					= 0x0C,

    Pro_W2D_ReportWifiStatus_Cmd 				= 0x0D,
    Pro_D2W_ReportWifiStatus_Ack_Cmd			= 0x0E,

    Pro_W2D_ReportMCUReset_Cmd 					= 0x0F,
    Pro_D2W_ReportMCUReset_Ack_Cmd				= 0x10,

    Pro_W2D_ErrorPackage_Cmd 					= 0x11,
    Pro_D2W_ErrorPackage_Ack_Cmd				= 0x12,

    /*3.10*/


} Pro_CmdTypeDef;


typedef enum
{
    SetLED_OnOff    = 0x01,
    SetLED_Color    = 0x02,
    SetLED_R       	= 0x04,
    SetLED_G    	= 0x08,
    SetLED_B  		= 0x10,
    SetMotor		= 0x20,

} Attr_FlagsTypeDef;

typedef enum
{
    LED_OnOff         = 0x00,
    LED_OnOn          = 0x01,
    LED_Costom        = 0x00,
    LED_Yellow    	  = 0x02,
    LED_Purple  	  = 0x04,
    LED_Pink		  = 0x06,

} LED_ColorTypeDef;


/******************************************************
* �ط����ƽṹ��
********************************************************/
__packed	typedef struct
{
    uint32_t        SendTime;//�ط���ϵͳʱ��
    uint8_t			SendNum;//�ط�����
    uint8_t			Flag;//1,��ʾ����Ҫ�ȴ���ACK;0,��ʾ����Ҫ�ȴ���ACK
    uint16_t        ResendBufLen;
    uint8_t			Cmd_Buff[Max_UartBuf];//�ط����ݻ�����
} Pro_Wait_AckTypeDef;


/******************************************************
* Э���׼ͷ
********************************************************/
__packed	typedef struct
{
    uint8_t							Head[2];
    uint16_t						Len;
    uint8_t							Cmd;
    uint8_t							SN;
    uint8_t							Flags[2];

} Pro_HeadPartTypeDef;

/******************************************************
* 4.1  WiFiģ�������豸��Ϣ
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  					Pro_HeadPart;
    uint8_t									Pro_ver[8];
    uint8_t									P0_ver[8];
    uint8_t									Hard_ver[8];
    uint8_t									Soft_ver[8];
    uint8_t									Product_Key[32];
    uint16_t								Binable_Time;
    uint8_t                                 devAttr[8];             ///< Device attribute
    uint8_t                                 productSecret[32];      ///< Product secret
    uint8_t									Sum;

} Pro_M2W_ReturnInfoTypeDef;

/*****************************************************
* Э��ͨ������֡(4.2��4.4��4.6��4.9��4.10)
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef    	Pro_HeadPart;
    uint8_t					Sum;
} Pro_CommonCmdTypeDef;


/******************************************************
* 4.3 �豸MCU֪ͨWiFiģ���������ģʽ
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    uint8_t                 	Config_Method;
    uint8_t						Sum;
} Pro_D2W_ConfigWifiTypeDef;


/*****************************************************
* WiFiģ�鹤��״̬
******************************************************/
#define 		Wifi_SoftAPMode       			(uint8_t)(1<<0)    //SoftAP
#define 		Wifi_StationMode      	    	(uint8_t)(1<<1)    //Station
#define 		Wifi_ConfigMode       		  	(uint8_t)(1<<2)    //
#define 		Wifi_BindingMode     			(uint8_t)(1<<3)    //
#define     	Wifi_ConnRouter             	(uint8_t)(1<<4)    //
#define     	Wifi_ConnClouds             	(uint8_t)(1<<5)    //
/*****************************************************
* 4.5 WiFiģ����MCU֪ͨWiFiģ�鹤��״̬�ı仯
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef    	Pro_HeadPart;
    uint16_t                Wifi_Status;
    uint8_t					Sum;
} Pro_W2D_WifiStatusTypeDef;

/*****************************************************
* �Ƿ���������
******************************************************/
typedef enum
{
    Error_AckSum = 0x01,      //У�����
    Error_Cmd 	 = 0x02,	  //���������
    Error_Other  = 0x03,      //����
} Error_PacketsTypeDef;


/*****************************************************
* 4.7 �Ƿ���Ϣ֪ͨ
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    Error_PacketsTypeDef		Error_Packets;
    uint8_t						Sum;
} Pro_ErrorCmdTypeDef;


/*****************************************************
* P0 command ������
******************************************************/
typedef enum
{
    P0_W2D_Control_Devce_Action 		= 0x01,
    P0_W2D_ReadDevStatus_Action 		= 0x02,
    P0_D2W_ReadDevStatus_Action_ACK 	= 0x03,
    P0_D2W_ReportDevStatus_Action   	= 0X04,

} P0_ActionTypeDef;


/******************************************************
* P0���ı�׼ͷ
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    P0_ActionTypeDef        	Action;
} Pro_HeadPartP0CmdTypeDef;

short	exchangeBytes(short	value);
uint8_t CheckSum( uint8_t *buf, int packLen );
void GizWits_init(uint8_t P0_Len);
void GizWits_D2WResetCmd(void);
void GizWits_D2WConfigCmd(uint8_t WiFi_Mode);
void GizWits_DevStatusUpgrade(uint8_t *P0_Buff, uint32_t Time, uint8_t flag);
void GizWits_WiFiStatueHandle(uint16_t wifiStatue);
u8 GizWits_MessageHandle(u8 * Message_Buf, u8 Length_buf);

#endif /*_PROTOCOL_H*/
