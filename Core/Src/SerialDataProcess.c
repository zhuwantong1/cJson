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


void SerialDataProcess()
{
    uint8_t len;
    if (g_usart_rx_sta & 0x8000)        /* ���յ������� */
    {
        len = g_usart_rx_sta & 0x3FFF;  /* ��ȡ��Ч���ݳ��� */
        g_usart_rx_buf[len] = '\0';     /* ĩβ��������� */
//        printf("���յ���JSON����: ");
//        printf(" %s\r\n",g_usart_rx_buf);
        cjson(g_usart_rx_buf);
        g_usart_rx_sta = 0;
        memset(g_usart_rx_buf, 0, sizeof(g_usart_rx_buf));
    }


}
