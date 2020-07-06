/**
********************************************************
*
* @file      main.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*            www.gizwits.com
*
*********************************************************/
/* Includes ------------------------------------------------------------------*/


#include "gokit.h"

/*Global Variable*/
uint32_t ReportTimeCount = 0;
uint8_t gaterSensorFlag = 0;
uint8_t Set_LedStatus = 0;
uint8_t NetConfigureFlag = 0;
uint8_t curTem = 0, curHum = 0;
uint8_t lastTem = 0,lastHum = 0;

extern RingBuffer u_ring_buff;
uint8_t p0Flag = 0;

WirteTypeDef_t  WirteTypeDef;
ReadTypeDef_t   ReadTypeDef;

static uint32_t PirTableSend[][FALLING_CNT*2]=
{
    //on
    {
    354, 148, 43, 127, 43, 125, 46, 43, 44, 41, 43, 43, 41, 125, 46, 44, 43, 41, 43, 125,
    44, 127, 43, 44, 44, 124, 46, 41, 43, 44, 41, 125, 54, 117, 46, 38, 46, 125, 46, 125,
    46, 41, 43, 44, 40, 128, 44, 43, 43, 41, 43, 125, 55, 30, 46, 43, 43, 41, 44, 43,
    41, 43, 44, 41, 43, 43, 44, 41, 43, 41, 43, 44, 43, 41, 44, 43, 41, 43, 43, 41,
    43, 44, 44, 40, 44, 43, 41, 125, 46, 43, 41, 43, 44, 125, 46, 41, 43, 43, 41, 125,
    46, 125, 46, 41, 43, 44, 41, 127, 43, 44, 43, 41, 44, 43, 41, 127, 43, 126, 46, 125,
    45, 126, 46, 41, 43, 44, 40, 44, 43, 41, 43, 125, 46, 41, 44, 125, 45, 44, 40, 44,
    44, 40, 44, 43, 43, 41, 43, 44, 41, 43, 44, 41, 43, 43, 41, 44, 43, 41, 43, 44,
    43, 41, 43, 44, 41, 43, 43, 41, 43, 44, 43, 40, 44, 40, 44, 43, 43, 41, 43, 43,
    41, 43, 44, 41, 43, 43, 44, 41, 43, 43, 41, 44, 43, 41, 44, 43, 41, 43, 43, 41,
    43, 44, 44, 40, 44, 43, 41, 43, 43, 41, 44, 43, 44, 40, 44, 41, 43, 43, 44, 41,
    43, 125, 46, 125, 46, 41, 48, 0,
    },
    //off
    {
    354, 149, 44, 127, 43, 125, 47, 43, 43, 41, 43, 44, 40, 125, 47, 43, 43, 41, 43, 125,
    44, 127, 43, 44, 44, 124, 46, 41, 43, 44, 41, 125, 46, 125, 46, 41, 43, 125, 46, 125,
    46, 41, 43, 44, 40, 128, 44, 43, 43, 41, 43, 125, 47, 40, 44, 43, 43, 41, 44, 43,
    41, 43, 44, 41, 43, 43, 44, 41, 43, 41, 43, 44, 43, 41, 44, 43, 40, 44, 43, 41,
    43, 44, 44, 40, 43, 44, 40, 44, 43, 41, 44, 40, 44, 125, 45, 44, 44, 40, 44, 125,
    43, 128, 46, 41, 43, 41, 43, 125, 46, 44, 40, 44, 43, 41, 44, 124, 46, 125, 44, 127,
    44, 125, 46, 43, 44, 40, 44, 43, 40, 44, 41, 128, 46, 40, 43, 125, 46, 38, 46, 43,
    40, 44, 43, 41, 43, 44, 43, 41, 43, 44, 41, 43, 43, 41, 43, 44, 40, 44, 44, 40,
    44, 43, 43, 41, 43, 44, 41, 43, 44, 40, 43, 43, 43, 42, 43, 41, 43, 44, 43, 41,
    43, 44, 41, 43, 43, 41, 43, 44, 40, 128, 44, 43, 43, 41, 43, 44, 41, 43, 44, 40,
    44, 43, 43, 41, 44, 43, 41, 43, 44, 41, 43, 43, 44, 41, 43, 125, 43, 128, 43, 125,
    46, 125, 46, 125, 46, 41, 49, 0,
    },
    //16°C
    {
    353, 149, 43, 128, 43, 125, 46, 44, 44, 40, 44, 43, 40, 126, 46, 43, 44, 40, 44, 125,
    43, 128, 51, 33, 45, 126, 46, 41, 43, 44, 40, 125, 46, 125, 46, 41, 44, 124, 46, 125,
    47, 40, 44, 43, 41, 127, 44, 43, 44, 41, 43, 125, 46, 41, 43, 44, 43, 41, 43, 44,
    41, 43, 43, 41, 43, 44, 43, 41, 44, 40, 44, 43, 43, 41, 43, 44, 41, 43, 44, 40,
    44, 43, 43, 40, 44, 43, 41, 125, 46, 43, 41, 44, 43, 125, 46, 41, 44, 43, 40, 125,
    46, 125, 47, 40, 43, 44, 40, 128, 44, 43, 43, 41, 43, 44, 41, 128, 43, 125, 46, 125,
    46, 125, 46, 41, 43, 44, 40, 44, 43, 41, 44, 124, 46, 41, 43, 125, 46, 43, 41, 43,
    43, 41, 43, 43, 44, 41, 43, 43, 42, 43, 43, 41, 43, 44, 40, 44, 44, 40, 44, 43,
    43, 41, 43, 44, 41, 43, 44, 40, 44, 43, 43, 41, 44, 41, 43, 43, 44, 41, 43, 43,
    42, 43, 43, 41, 43, 44, 43, 41, 44, 43, 41, 43, 43, 41, 43, 44, 41, 43, 44, 40,
    44, 43, 43, 41, 44, 43, 41, 43, 44, 40, 44, 43, 44, 40, 43, 41, 43, 43, 43, 41,
    44, 124, 46, 125, 47, 40, 49, 0,
    },
    //17
    {
    354, 148, 43, 128, 44, 124, 46, 44, 44, 40, 44, 43, 41, 125, 46, 43, 44, 40, 44, 125,
    43, 128, 43, 44, 43, 125, 46, 41, 43, 44, 40, 125, 47, 124, 46, 41, 44, 125, 45, 126,
    46, 40, 43, 43, 41, 128, 43, 44, 43, 41, 43, 125, 46, 41, 43, 44, 43, 41, 43, 44,
    41, 43, 43, 41, 43, 44, 43, 41, 44, 40, 44, 43, 43, 41, 44, 43, 41, 43, 44, 41,
    43, 43, 43, 41, 43, 43, 41, 125, 47, 43, 41, 43, 43, 125, 47, 40, 44, 43, 41, 125,
    45, 125, 46, 40, 44, 43, 40, 128, 43, 43, 44, 41, 44, 42, 43, 41, 43, 125, 44, 127,
    43, 125, 47, 43, 44, 40, 44, 43, 40, 44, 40, 128, 46, 40, 44, 125, 46, 41, 43, 43,
    41, 44, 43, 41, 43, 44, 43, 41, 43, 44, 41, 43, 43, 41, 43, 44, 40, 44, 44, 40,
    44, 43, 43, 41, 43, 44, 41, 43, 44, 40, 43, 43, 43, 41, 43, 41, 43, 43, 43, 41,
    43, 44, 41, 43, 43, 41, 43, 44, 43, 41, 44, 43, 41, 43, 43, 41, 43, 44, 41, 43,
    44, 40, 44, 43, 43, 41, 44, 43, 41, 43, 41, 128, 44, 124, 46, 125, 47, 124, 46, 125,
    47, 40, 44, 124, 46, 41, 49, 0,
    },
    //18
    {
    354, 149, 43, 128, 43, 125, 46, 43, 44, 41, 43, 44, 40, 125, 46, 44, 43, 41, 43, 125,
    44, 127, 43, 44, 44, 124, 45, 41, 43, 44, 41, 125, 46, 125, 46, 41, 43, 125, 46, 125,
    46, 41, 43, 44, 40, 128, 44, 40, 46, 41, 43, 126, 46, 40, 43, 43, 43, 42, 43, 43,
    41, 44, 43, 41, 43, 44, 43, 41, 43, 41, 43, 44, 43, 40, 44, 43, 41, 43, 43, 41,
    43, 43, 44, 40, 44, 43, 41, 125, 46, 41, 43, 41, 46, 125, 46, 38, 46, 41, 43, 125,
    47, 124, 46, 39, 45, 41, 44, 127, 44, 41, 45, 41, 44, 41, 43, 128, 43, 41, 44, 127,
    43, 125, 47, 40, 46, 38, 46, 41, 43, 41, 44, 127, 46, 38, 46, 125, 47, 38, 46, 40,
    42, 42, 46, 38, 46, 41, 46, 38, 45, 42, 43, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 46, 38, 46, 41, 44, 40, 46, 38, 46, 41, 46, 38, 47, 38, 46, 41, 45, 39,
    45, 41, 43, 41, 46, 38, 46, 41, 45, 39, 46, 41, 43, 41, 46, 38, 46, 41, 44, 40,
    46, 38, 46, 41, 46, 38, 47, 40, 44, 40, 46, 39, 45, 125, 46, 125, 43, 128, 43, 125,
    46, 41, 43, 128, 43, 41, 51, 0,
    },
    //19
    {
    354, 148, 43, 128, 44, 124, 46, 41, 47, 37, 47, 40, 44, 125, 46, 40, 46, 38, 46, 125,
    43, 128, 43, 41, 46, 125, 46, 38, 46, 41, 43, 125, 46, 125, 46, 38, 47, 124, 46, 125,
    47, 38, 46, 40, 44, 127, 44, 41, 46, 38, 46, 125, 46, 38, 46, 41, 46, 38, 46, 41,
    44, 40, 46, 38, 46, 41, 46, 38, 47, 37, 46, 41, 46, 38, 46, 41, 44, 40, 46, 38,
    46, 41, 46, 38, 47, 40, 44, 125, 45, 41, 44, 41, 46, 125, 45, 39, 46, 41, 43, 125,
    46, 125, 46, 38, 46, 41, 43, 128, 44, 40, 46, 38, 46, 41, 46, 37, 47, 40, 44, 125,
    45, 125, 46, 38, 46, 41, 45, 39, 46, 41, 43, 125, 46, 41, 44, 124, 46, 41, 46, 38,
    47, 40, 43, 41, 46, 38, 46, 41, 47, 37, 46, 41, 43, 41, 46, 39, 46, 40, 44, 41,
    45, 39, 45, 42, 46, 38, 46, 41, 43, 41, 45, 39, 46, 41, 46, 38, 46, 38, 46, 41,
    46, 38, 46, 41, 43, 41, 46, 38, 47, 40, 46, 38, 46, 41, 43, 41, 47, 38, 46, 40,
    44, 41, 45, 39, 46, 41, 46, 38, 46, 41, 43, 125, 46, 41, 43, 125, 47, 124, 46, 125,
    46, 38, 46, 125, 46, 41, 52, 0,
    },
    //20
    {
    354, 149, 43, 128, 43, 125, 46, 41, 46, 38, 46, 41, 44, 124, 46, 41, 46, 38, 47, 124,
    44, 127, 44, 41, 46, 125, 45, 39, 46, 41, 43, 125, 46, 125, 46, 38, 46, 125, 47, 124,
    46, 38, 46, 41, 44, 127, 44, 40, 46, 39, 46, 125, 46, 38, 46, 41, 46, 38, 46, 41,
    43, 41, 46, 38, 46, 40, 46, 38, 46, 38, 46, 41, 47, 37, 47, 40, 44, 40, 46, 39,
    46, 40, 47, 38, 46, 40, 44, 125, 46, 41, 43, 41, 46, 125, 46, 38, 46, 41, 43, 125,
    47, 124, 46, 38, 47, 40, 44, 127, 43, 41, 46, 38, 46, 40, 44, 127, 44, 125, 46, 41,
    43, 125, 46, 41, 46, 38, 46, 41, 44, 40, 44, 127, 46, 38, 47, 124, 46, 38, 46, 41,
    43, 41, 46, 38, 46, 41, 45, 39, 46, 40, 43, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 46, 38, 46, 41, 44, 40, 46, 38, 46, 41, 46, 37, 47, 38, 46, 40, 46, 39,
    45, 41, 44, 41, 46, 38, 46, 41, 45, 39, 46, 41, 43, 41, 46, 38, 46, 41, 44, 40,
    46, 38, 46, 41, 46, 38, 47, 40, 44, 40, 46, 39, 45, 41, 44, 125, 46, 125, 46, 125,
    46, 38, 46, 125, 46, 41, 51, 0,
    },
    //21
    {
    353, 149, 44, 127, 43, 126, 46, 40, 45, 39, 45, 41, 43, 125, 46, 41, 45, 39, 46, 125,
    43, 128, 44, 40, 46, 125, 46, 38, 47, 40, 44, 125, 45, 126, 46, 38, 46, 125, 46, 125,
    46, 38, 46, 41, 44, 127, 43, 41, 46, 38, 47, 124, 46, 38, 46, 41, 47, 37, 47, 40,
    44, 40, 46, 39, 46, 40, 47, 38, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 46, 38, 46, 41, 43, 125, 46, 41, 43, 41, 46, 125, 46, 38, 46, 41, 43, 126,
    46, 125, 45, 39, 46, 41, 43, 128, 43, 41, 46, 38, 46, 41, 46, 38, 46, 125, 46, 38,
    46, 125, 47, 37, 46, 40, 46, 39, 45, 41, 44, 125, 46, 41, 43, 125, 46, 41, 46, 38,
    46, 41, 44, 40, 46, 38, 46, 41, 46, 38, 46, 40, 44, 40, 46, 38, 46, 41, 43, 41,
    47, 38, 46, 40, 46, 39, 45, 41, 44, 41, 46, 38, 46, 41, 45, 39, 46, 38, 46, 41,
    46, 38, 46, 41, 44, 40, 46, 38, 46, 41, 46, 38, 47, 40, 44, 40, 46, 39, 45, 41,
    44, 41, 46, 38, 46, 41, 45, 39, 46, 41, 43, 125, 46, 125, 46, 38, 46, 125, 47, 124,
    46, 38, 46, 125, 46, 40, 51, 0,
    },
    //22
    {
    354, 148, 43, 128, 44, 124, 46, 41, 46, 38, 47, 40, 44, 125, 45, 41, 46, 38, 46, 125,
    43, 128, 43, 41, 46, 125, 46, 38, 46, 41, 43, 125, 47, 124, 46, 39, 45, 126, 46, 125,
    45, 39, 46, 41, 43, 128, 43, 41, 46, 38, 46, 125, 46, 38, 47, 40, 46, 38, 46, 41,
    43, 41, 47, 37, 47, 40, 46, 38, 46, 39, 46, 40, 47, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 46, 38, 46, 41, 44, 124, 46, 41, 43, 41, 47, 124, 46, 38, 46, 41, 44, 125,
    46, 125, 46, 38, 46, 41, 43, 128, 43, 41, 46, 38, 46, 41, 43, 128, 43, 41, 46, 38,
    46, 125, 46, 38, 46, 41, 46, 38, 46, 40, 44, 125, 45, 42, 43, 125, 46, 41, 45, 39,
    46, 41, 43, 41, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38, 46, 40, 44, 40,
    45, 39, 45, 41, 46, 38, 46, 41, 43, 41, 45, 39, 46, 41, 46, 38, 46, 38, 46, 41,
    46, 38, 46, 41, 43, 41, 46, 38, 47, 40, 46, 38, 46, 41, 43, 41, 47, 38, 46, 40,
    44, 41, 45, 39, 46, 41, 46, 38, 46, 41, 43, 41, 44, 127, 46, 38, 46, 125, 44, 127,
    43, 41, 47, 124, 46, 38, 51, 0,
    },
    //23
    {
    354, 149, 43, 128, 43, 125, 46, 41, 46, 38, 46, 41, 43, 125, 46, 41, 46, 38, 46, 125,
    44, 127, 43, 41, 46, 124, 46, 39, 45, 41, 43, 125, 46, 125, 46, 38, 46, 125, 46, 125,
    46, 38, 46, 41, 43, 128, 44, 40, 46, 38, 46, 125, 47, 37, 47, 40, 46, 38, 45, 41,
    44, 41, 46, 38, 46, 41, 45, 38, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 45, 38, 46, 41, 43, 125, 46, 41, 44, 40, 46, 125, 46, 39, 46, 40, 44, 125,
    45, 126, 46, 38, 46, 41, 43, 128, 43, 41, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41,
    43, 128, 44, 40, 46, 39, 45, 41, 47, 38, 46, 125, 45, 39, 46, 125, 46, 38, 46, 41,
    46, 38, 46, 41, 43, 41, 46, 38, 47, 40, 46, 38, 46, 41, 43, 41, 47, 37, 47, 40,
    44, 40, 46, 39, 46, 40, 47, 38, 46, 40, 44, 41, 46, 38, 46, 41, 46, 38, 46, 38,
    47, 40, 46, 38, 46, 41, 43, 41, 47, 37, 46, 41, 46, 38, 46, 41, 44, 40, 47, 37,
    46, 41, 43, 41, 47, 38, 46, 40, 46, 38, 45, 126, 46, 38, 46, 41, 43, 125, 46, 125,
    46, 41, 43, 124, 46, 41, 51, 0,
    },
    //24
    {
    354, 149, 43, 128, 43, 125, 46, 41, 46, 38, 46, 41, 44, 124, 46, 41, 46, 38, 46, 124,
    44, 127, 43, 40, 47, 124, 46, 39, 46, 40, 44, 125, 45, 126, 46, 38, 46, 125, 46, 125,
    46, 38, 46, 41, 44, 127, 43, 41, 46, 38, 47, 124, 46, 38, 45, 41, 47, 37, 47, 40,
    44, 40, 45, 39, 46, 40, 47, 38, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 40, 46, 38, 46, 41, 43, 125, 47, 40, 44, 40, 46, 125, 47, 37, 47, 40, 43, 126,
    46, 125, 45, 39, 45, 41, 43, 128, 43, 41, 45, 38, 46, 41, 43, 128, 43, 124, 46, 125,
    46, 38, 47, 40, 46, 38, 46, 41, 43, 41, 44, 127, 45, 39, 45, 126, 46, 38, 46, 41,
    43, 41, 46, 38, 46, 41, 46, 38, 46, 41, 44, 40, 46, 38, 46, 41, 43, 41, 47, 37,
    47, 40, 46, 38, 46, 41, 44, 40, 47, 38, 45, 41, 46, 39, 46, 38, 46, 41, 45, 39,
    45, 42, 43, 41, 46, 38, 46, 41, 45, 39, 46, 41, 43, 41, 46, 38, 46, 41, 44, 40,
    46, 38, 46, 41, 46, 38, 47, 40, 44, 40, 46, 39, 45, 41, 47, 38, 46, 125, 43, 128,
    43, 41, 46, 125, 46, 38, 51, 0,
    },
    //25
    {
    354, 149, 43, 128, 43, 125, 51, 36, 46, 38, 46, 41, 43, 125, 46, 41, 46, 38, 46, 125,
    43, 128, 44, 40, 46, 125, 47, 38, 46, 40, 44, 125, 46, 125, 46, 38, 46, 125, 46, 125,
    46, 38, 47, 40, 43, 128, 43, 41, 47, 37, 46, 125, 46, 38, 47, 40, 46, 38, 45, 41,
    43, 41, 46, 38, 46, 40, 46, 39, 45, 39, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38,
    46, 41, 46, 38, 46, 41, 44, 124, 46, 41, 43, 41, 47, 124, 46, 38, 46, 41, 44, 125,
    46, 125, 46, 38, 46, 41, 43, 128, 43, 41, 46, 38, 46, 41, 46, 38, 46, 125, 43, 128,
    44, 40, 46, 38, 46, 41, 46, 38, 47, 40, 44, 125, 45, 41, 44, 125, 46, 41, 45, 39,
    46, 41, 43, 41, 46, 38, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38, 46, 40, 44, 40,
    46, 38, 46, 41, 47, 37, 47, 40, 44, 40, 46, 38, 45, 40, 47, 37, 46, 38, 45, 41,
    46, 38, 46, 40, 44, 41, 45, 39, 46, 41, 46, 38, 46, 41, 43, 41, 45, 38, 46, 41,
    43, 41, 46, 38, 46, 40, 46, 38, 46, 41, 43, 125, 47, 124, 46, 125, 47, 38, 46, 125,
    45, 39, 46, 125, 46, 41, 51, 0,
    },
    //26
    {
    360, 143, 43, 127, 43, 125, 46, 40, 46, 38, 46, 41, 43, 125, 47, 40, 46, 38, 46, 125,
    44, 127, 44, 41, 45, 126, 51, 33, 46, 41, 43, 125, 46, 125, 46, 38, 47, 124, 46, 125,
    47, 37, 46, 40, 44, 127, 44, 41, 46, 38, 46, 125, 46, 38, 46, 41, 46, 38, 46, 41,
    44, 40, 46, 38, 46, 41, 46, 38, 47, 37, 47, 40, 46, 38, 46, 40, 44, 40, 47, 38,
    46, 41, 45, 38, 46, 41, 43, 125, 46, 40, 43, 41, 46, 125, 46, 37, 47, 40, 43, 125,
    47, 124, 47, 38, 45, 41, 43, 127, 43, 41, 45, 39, 46, 41, 43, 128, 43, 41, 43, 127,
    43, 41, 46, 38, 47, 40, 46, 38, 46, 41, 43, 126, 46, 40, 43, 125, 46, 41, 46, 38,
    46, 41, 43, 41, 47, 37, 46, 41, 46, 38, 46, 41, 44, 40, 47, 37, 46, 41, 43, 41,
    45, 38, 46, 40, 46, 38, 45, 41, 43, 41, 46, 38, 46, 41, 46, 38, 46, 38, 46, 41,
    46, 38, 46, 41, 44, 40, 46, 38, 46, 41, 46, 38, 47, 40, 44, 40, 46, 39, 45, 41,
    44, 41, 46, 38, 46, 41, 45, 39, 46, 41, 43, 41, 43, 128, 44, 124, 52, 35, 43, 128,
    44, 40, 46, 125, 47, 38, 51, 0,
    },
    //27
    {
    354, 149, 43, 127, 43, 125, 46, 40, 46, 38, 46, 41, 43, 125, 47, 40, 46, 38, 46, 125,
    44, 127, 44, 41, 45, 126, 46, 38, 46, 41, 43, 125, 46, 125, 46, 38, 47, 124, 46, 125,
    47, 37, 47, 40, 44, 127, 44, 41, 46, 38, 46, 125, 46, 38, 46, 41, 46, 38, 46, 41,
    44, 40, 46, 38, 46, 41, 46, 38, 47, 37, 47, 40, 46, 38, 46, 41, 44, 40, 47, 38,
    46, 40, 46, 39, 46, 40, 44, 125, 46, 41, 44, 40, 46, 125, 46, 38, 47, 40, 44, 124,
    46, 125, 47, 38, 46, 40, 43, 128, 44, 41, 46, 38, 46, 41, 46, 38, 46, 41, 43, 125,
    46, 41, 43, 41, 46, 38, 46, 41, 47, 37, 46, 125, 46, 39, 46, 124, 45, 39, 45, 42,
    46, 38, 46, 41, 43, 41, 45, 39, 46, 41, 46, 38, 46, 41, 43, 41, 46, 38, 46, 41,
    43, 41, 46, 38, 47, 40, 46, 38, 46, 41, 43, 42, 46, 38, 46, 41, 45, 39, 45, 39,
    46, 41, 46, 38, 46, 41, 43, 41, 46, 38, 46, 41, 46, 38, 46, 41, 44, 40, 46, 39,
    45, 41, 43, 42, 46, 38, 46, 41, 45, 39, 45, 126, 46, 38, 46, 125, 46, 38, 46, 125,
    46, 41, 44, 124, 46, 41, 51, 0,
    },
};

uint8_t temp_cout;

extern uint32_t SystemTimeCount;
extern uint32_t Pir_TimeCount ;
uint32_t lowCnt   = 0;
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t p0_control_buf[MAX_P0_LEN];
    SystemInit();
    HW_Init();
    Printf_SystemRccClocks();
    SW_Init();
    while(1)
    {
        KEY_Handle();

        GizWits_MessageHandle(p0_control_buf, sizeof(WirteTypeDef_t));
        if(p0Flag == 1)
        {
            memcpy((uint8_t *)&WirteTypeDef, p0_control_buf, sizeof(WirteTypeDef_t));
            GizWits_ControlDeviceHandle();
            GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 1);
            p0Flag =0;
        }
        if(gaterSensorFlag != 0)
        {
                GizWits_GatherSensorData();
                gaterSensorFlag = 0;
        }
        GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 0);

        // Delay_ms(3000);
        // printf("lowCnt=%d\r\n",lowCnt);
        // lowCnt = 0;
        // get_IrCode();

    }
}
/** @addtogroup GizWits_HW_Init
  * @{
  */
void HW_Init(void)
{
    Delay_Init(72);
    UARTx_Init();
    Motor_Init();
    RGB_KEY_GPIO_Init();
    RGB_LED_Init();
    LED_GPIO_Init();
    KEY_GPIO_Init();
//  TIM3_Int_Init(7199,9);   //ms interrupt
    TIM3_Int_Init(72-1,10-1);   //10us interrupt

    Pir_Init();
    Hal_PirRec_Init();
}
/** @addtogroup GizWits_SW_Init
  * @{
  */
void SW_Init()
{
    ReadTypeDef.ON_OFF = 0;
    ReadTypeDef.Temp = 0;
    GizWits_init(sizeof(ReadTypeDef_t));
    printf("Gokit Init Ok ...\r\n");
}
/** @addtogroup Printf_SystemRccClocks
  * @{
  */
void Printf_SystemRccClocks(void)
{
    uint8_t SYSCLKSource;

    RCC_ClocksTypeDef  SystemRCC_Clocks;
    printf("System start...\r\n");
    SYSCLKSource = RCC_GetSYSCLKSource();
    if(SYSCLKSource==0x04)
        printf("SYSCLKSource is HSE\r\n");
    else if(SYSCLKSource==0x00)
        printf("SYSCLKSource is HSI\r\n");
    else if(SYSCLKSource==0x08)
        printf("SYSCLKSource is PL!\r\n");

    RCC_GetClocksFreq(&SystemRCC_Clocks);
    printf("SYS clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.SYSCLK_Frequency/1000000);
    printf("HCLK clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.HCLK_Frequency/1000000);
    printf("PCLK1 clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK1_Frequency/1000000);
    printf("PCLK2_clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK2_Frequency/1000000);
    printf("SADCCLK_Frequencyclock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.ADCCLK_Frequency/1000000);
}

/*******************************************************************************
* Function Name  : GizWits_ControlDeviceHandle
* Description    : Analy P0 Package
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention      :
*******************************************************************************/
void GizWits_ControlDeviceHandle()
{
    uint8_t temp;

    if( (WirteTypeDef.Attr_Flags & (1<<0)) == (1<<0))
    {
        ReadTypeDef.ON_OFF = WirteTypeDef.ON_OFF;
        if(WirteTypeDef.ON_OFF == 1)
        {
        printf("switch ON \r\n");
        PirSend( PirTableSend[SWITCH_ON] );
        }
        else
        {
            printf("switch OFF \r\n");
            PirSend( PirTableSend[SWITCH_OFF] );
        }

    }

    if( (WirteTypeDef.Attr_Flags & (1<<1)) == (1<<1))
    {

        temp = WirteTypeDef.Temp+16;
        ReadTypeDef.Temp = WirteTypeDef.Temp;
        printf("Temp = %d\r\n",temp);
        switch (temp)
        {
            case 16:PirSend( PirTableSend[TEMP_16] );
                break;
            case 17:PirSend( PirTableSend[TEMP_17] );
                break;
            case 18:PirSend( PirTableSend[TEMP_18] );
                break;
            case 19:PirSend( PirTableSend[TEMP_19] );
                break;
            case 20:PirSend( PirTableSend[TEMP_20] );
                break;
            case 21:PirSend( PirTableSend[TEMP_21] );
                break;
            case 22:PirSend( PirTableSend[TEMP_22] );
                break;
            case 23:PirSend( PirTableSend[TEMP_23] );
                break;
            case 24:PirSend( PirTableSend[TEMP_24] );
                break;
            case 25:PirSend( PirTableSend[TEMP_25] );
                break;
            case 26:PirSend( PirTableSend[TEMP_26] );
                break;
            case 27:PirSend( PirTableSend[TEMP_27] );
                break;
            default:
                break;
        }

    }

}
/*******************************************************************************
* Function Name  : GizWits_GatherSensorData();
* Description    : Gather Sensor Data
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void GizWits_GatherSensorData(void)
{
//  ReadTypeDef.Infrared = IR_Handle();
//  DHT11_Read_Data(&curTem, &curHum);
//  ReadTypeDef.Temperature = (curTem + lastTem) /2;
//  ReadTypeDef.Humidity = (curHum + lastHum)/2;

//  ReadTypeDef.Temperature = ReadTypeDef.Temperature + 13;//Temperature Data Correction
//  lastTem = curTem;
//  lastHum = curHum;
}
/*******************************************************************************
* Function Name  : KEY_Handle
* Description    : Key processing function
* Input          : None
* Output         : None
* Return         : None
* Attention          : None
*******************************************************************************/
void KEY_Handle(void)
{
    uint8_t Key_return =0;
    Key_return = ReadKeyValue();
    if(Key_return & KEY_UP)
    {
        if(Key_return & PRESS_KEY1)
        {
        #ifdef PROTOCOL_DEBUG
                  printf("KEY1 PRESS\r\n");
        #endif
            temp_cout++;
            if(temp_cout >= 17)
                temp_cout = 17;
        LED_RGB_Control(0,10,0);
        LED_RGB_Control(0,0,0);
        }
        if(Key_return & PRESS_KEY2)
        {
            #ifdef PROTOCOL_DEBUG
            printf("KEY2 PRESS ,Soft AP mode\r\n");
            #endif
            //Soft AP mode, RGB red
            LED_RGB_Control(255, 0, 0);
            GizWits_D2WConfigCmd(SoftAp_Mode);
            NetConfigureFlag = 1;
        }
    }

    if(Key_return & KEY_LONG)
    {
        if(Key_return & PRESS_KEY1)
        {
            #ifdef PROTOCOL_DEBUG
                printf("KEY1 PRESS LONG ,Wifi Reset\r\n");
            #endif
            GizWits_D2WResetCmd();
        }
        if(Key_return & PRESS_KEY2)
        {
            //AirLink mode, RGB Green
            #ifdef PROTOCOL_DEBUG
            printf("KEY2 PRESS LONG ,AirLink mode\r\n");
            #endif
            LED_RGB_Control(0, 128, 0);
            GizWits_D2WConfigCmd(AirLink_Mode);
            NetConfigureFlag = 1;
        }
    }
}
/*******************************************************************************
* Function Name  : GizWits_WiFiStatueHandle
* Description    : Callback function , Judge Wifi statue
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention      :
*******************************************************************************/
void GizWits_WiFiStatueHandle(uint16_t wifiStatue)
{
    if(((wifiStatue & Wifi_ConnClouds) == Wifi_ConnClouds) && (NetConfigureFlag == 1))
    {
        printf("W2M->Wifi_ConnClouds\r\n");
        NetConfigureFlag = 0;
        LED_RGB_Control(0,0,0);
    }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
