//
// Created by zhu on 2024/1/29.
//
#include <stdbool.h>
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "cJSON_Test.h"
#include "SerialDataProcess.h"
#include "Communication_Protocol.h"
extern  bool Printf_Flag ;
uint8_t  cjson_buf[200];
void SerialDataProcess()
{
    uint8_t len;
    if (g_usart_rx_sta & 0x8000)        /* ���յ������� */
    {
        len = g_usart_rx_sta & 0x3FFF;  /* ��ȡ��Ч���ݳ��� */
        g_usart_rx_buf[len] = '\0';     /* ĩβ��������� */
        printf("���յ���JSON����: ");
        printf(" %s\r\n",g_usart_rx_buf);

        //IRIS_Cut_Befor_Header(g_usart_rx_buf,len);
        IRIS_Protocol_Unpack(g_usart_rx_buf, len, 0x00, cjson_buf);
        printf("�и�֮�� %s\r\n",cjson_buf);
        cjson(cjson_buf);
//

        g_usart_rx_sta = 0;
        memset(g_usart_rx_buf, 0, sizeof(g_usart_rx_buf));
    }else
    {
        Printf_Flag = false;
    }


}
