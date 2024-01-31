#include "Communication_Protocol.h"
#include "string.h"


int32_t IRIS_Protocol_Pack(uint8_t Command,uint16_t LenthofIn, uint8_t *BufferIn, uint8_t *PackData)
{
    if( PackData == NULL || (LenthofIn!=0 && BufferIn == NULL))
    {
        return -1;
    }

    PackData[0] = 0x55;
    PackData[1] = 0xAA;
    PackData[2] = Command;
    PackData[3] = LenthofIn & 0xFF;
    PackData[4] = (LenthofIn >> 8) & 0xFF;
    if(LenthofIn!=0)
    {
        memcpy(&PackData[5],BufferIn,LenthofIn);
    }
    uint16_t CRC = IRIS_calcCRC(PackData, LenthofIn+5);
    PackData[LenthofIn+5] = CRC & 0xFF;
    PackData[LenthofIn+6] = (CRC >> 8) & 0xFF;
    return LenthofIn+7;






}

int32_t IRIS_STM32_Protocol_Unpack(uint8_t *PackData, uint16_t LenthofIn, uint8_t *Command, uint8_t *BufferOut)
{

    if( PackData == NULL || BufferOut == NULL)
    {
        return ERROR_INPUT;
    }
    if(PackData[0] != 0x55 || PackData[1] != 0xAA)
    {
        return ERROR_HEADER;
    }

    uint16_t LenthofOut = PackData[3] + (PackData[4] << 8);
    if(LenthofOut > LenthofIn - 7)
    {
        return ERROR_NOT_ENOUGH_DATA;
    }
    uint16_t CRC = IRIS_calcCRC(PackData, LenthofOut+5);
    if(CRC != (PackData[LenthofOut+5] + (PackData[LenthofOut+6] << 8)))
    {
        return ERROR_CRC;
    }
    if(LenthofOut == 0)
    {
        return 0;
    }
    *Command = PackData[2] ;

    memcpy(BufferOut,&PackData[5],LenthofOut);
    return LenthofOut;
}


int32_t IRIS_Protocol_Unpack(uint8_t *PackData, uint16_t LenthofIn, uint8_t Command, uint8_t *BufferOut)
{
    if( PackData == NULL || BufferOut == NULL)
    {
        return ERROR_INPUT;
    }
    if(PackData[0] != 0x55 || PackData[1] != 0xAA)
    {
        return ERROR_HEADER;
    }
    if(PackData[2] != Command)
    {
        return ERROR_COMMAND;
    }
    uint16_t LenthofOut = *(uint16_t *)(PackData+3)-2;
    if(LenthofOut > LenthofIn - 7)
    {
        return ERROR_NOT_ENOUGH_DATA;
    }
    uint16_t CRC = IRIS_calcCRC(PackData, LenthofOut+5);
    uint16_t CRC2=*(uint16_t *)(PackData+LenthofOut+5);
    if(CRC !=  CRC2)
    {
        return ERROR_CRC;
    }
    if(LenthofOut == 0)
    {
        return 0;
    }
    memcpy(BufferOut,&PackData[5],LenthofOut);
    return LenthofOut;

}


int32_t IRIS_Cut_Befor_Header(uint8_t *PackData, uint16_t LenthofIn )
{
    if( PackData == NULL )
    {
        return ERROR_INPUT;
    }
    uint16_t i = 0;
    for(i = 0; i < LenthofIn; i++)
    {
        if(PackData[i] == 0x55 && PackData[i+1] == 0xAA)
        {
            break;
        }
    }
    if(i == LenthofIn)
    {
        //清空数据
        memset(PackData,0,LenthofIn);
        return 0;
    }

    uint16_t LenthofOut = LenthofIn - i;
    memcpy(PackData,&PackData[i],LenthofOut);
    return LenthofOut;
}

int32_t IRIS_Check_Data_Valid(uint8_t *PackData, uint16_t LenthofIn)
{
    if( PackData == NULL)
    {
        return ERROR_INPUT;
    }
    if (LenthofIn < 7)
    {
        return ERROR_NOT_ENOUGH_DATA;
        /* code */
    }

    if(PackData[0] != 0x55 || PackData[1] != 0xAA)
    {
        return ERROR_HEADER;
    }
    uint16_t LenthofOut = PackData[3] + (PackData[4] << 8);
    if(LenthofOut > LenthofIn - 7)
    {
        return ERROR_NOT_ENOUGH_DATA;
    }
    uint16_t CRC = IRIS_calcCRC(PackData, LenthofOut+5);
    if(CRC != (PackData[LenthofOut+5] + (PackData[LenthofOut+6] << 8)))
    {
        return ERROR_CRC;
    }
    return 1;

}







uint16_t IRIS_calcCRC(const void *pBuffer, uint16_t bufferSize)
{
    const uint8_t *pBytesArray = (const uint8_t*)pBuffer;
    uint16_t poly = 0x8408;
    uint16_t crc = 0;
    uint8_t carry;
    uint8_t i_bits;
    uint16_t j;
    for (j =0; j < bufferSize; j++)
    {
        crc = crc ^ pBytesArray[j];
        for (i_bits = 0; i_bits < 8; i_bits++)
        {
            carry = crc & 1;
            crc = crc / 2;
            if (carry)
            {
                crc = crc^poly;
            }
        }
    }
    return crc;
}

