//
// Created by zhu on 2024/1/29.
//
#include "cJSON.h"
#ifndef H750_CJSON_CJSON_TEST_H
#define H750_CJSON_CJSON_TEST_H
struct paramstruct {
    int age;
    float height;
};
//void cjson(const char * g_usart_json_string);
void cjson(uint8_t g_usart_json_string[]);
void parseNestedObject(cJSON *nestedObject);
int Change_Age();
struct paramstruct *GetParametesptr();
void SV_Change_Age();
#endif //H750_CJSON_CJSON_TEST_H
