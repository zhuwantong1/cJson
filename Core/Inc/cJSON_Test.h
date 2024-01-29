//
// Created by zhu on 2024/1/29.
//
#include "cJSON.h"
#ifndef H750_CJSON_CJSON_TEST_H
#define H750_CJSON_CJSON_TEST_H
//void cjson(const char * g_usart_json_string);
void cjson(uint8_t g_usart_json_string[]);
void parseNestedObject(cJSON *nestedObject);
#endif //H750_CJSON_CJSON_TEST_H
