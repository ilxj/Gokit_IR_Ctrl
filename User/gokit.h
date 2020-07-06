#ifndef _GOKIT_H
#define _GOKIT_H

#include "stm32f10x.h"
#include "Hal_key/Hal_key.h"
#include "Hal_led/Hal_led.h"
#include "Hal_motor/Hal_motor.h"
#include "Hal_rgb_led/Hal_rgb_led.h"
#include "Hal_temp_hum/Hal_temp_hum.h"
#include "Hal_infrared/Hal_infrared.h"
#include "Hal_Usart/hal_uart.h"
#include "ringbuffer.h"
#include "Protocol.h"
#include <string.h>
#include "Hal_PIR/hal_PIR.h"
#include "Hal_PIR/Hal_PIR_Rec.h"

__packed	typedef struct	
{
	uint8_t							ON_OFF;
	uint8_t							Temp;
}ReadTypeDef_t; 

__packed typedef struct	
{
	uint8_t					    Attr_Flags;
	uint8_t							ON_OFF;
	uint8_t							Temp;
	
	
}WirteTypeDef_t;

void HW_Init(void);
void Printf_SystemRccClocks(void);
void GizWits_GatherSensorData(void);
void GizWits_ControlDeviceHandle(void);
void SW_Init(void);
void KEY_Handle(void);
//void GizWits_WiFiStatueHandle(uint16_t wifiStatue);

#endif
