
#include <stdio.h>
#include "cJSON_Test.h"

void cjson(uint8_t g_usart_json_string[])
{
    const char * json_string = g_usart_json_string;
    printf("JSON string: %s\r\n", json_string);
    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
    // 获取 JSON 对象中的值
        cJSON *name = cJSON_GetObjectItem(json, "name");
        cJSON *age  = cJSON_GetObjectItem(json, "age");
        cJSON *city = cJSON_GetObjectItem(json, "city");
        cJSON *waihao = cJSON_GetObjectItem(json, "waihao");
        if (name != NULL && age != NULL && city != NULL&& waihao != NULL) {
    // 打印解析结果
        printf("Name: %s\n", name->valuestring);
        printf("Age: %d\n", age->valueint);
        printf("City: %s\n", city->valuestring);
        // 解析嵌套的对象
        printf("Waihao:\n");
        parseNestedObject(waihao);
        }

// 释放 cJSON 对象
        cJSON_Delete(json);
    } else {
// 处理解析错误
        printf("JSON parsing error.\n");
    }
}
void parseNestedObject(cJSON *nestedObject) {
    cJSON *waihao1 = cJSON_GetObjectItem(nestedObject, "waihao1");
    cJSON *waihao2 = cJSON_GetObjectItem(nestedObject, "waihao2");

    if (waihao1 != NULL && waihao2 != NULL) {
        // 打印嵌套对象的属性
        printf("  waihao1: %s\n", waihao1->valuestring);
        printf("  waihao2: %s\n", waihao2->valuestring);
    }
}