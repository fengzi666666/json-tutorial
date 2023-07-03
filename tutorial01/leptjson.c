#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)
//检查一个字符是否与给定的字符相匹配。
typedef struct {
    const char* json;
}lept_context;//定义了一个名为lept_context的结构体，其中包含一个名为json的常量字符指针。

static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');//使用宏EXPECT来判断输入的JSON字符串是否以字符'n'开头
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;//通过判断c->json[0]、c->json[1]和c->json[2]是否分别为'u'、'l'和'l'来判断输入的JSON字符串是否为null
    c->json += 3;//如果输入的JSON字符串是null，则将c->json的指针向后移动3个位置，跳过"null"这个字符串
    v->type = LEPT_NULL;//将v的type字段设置为LEPT_NULL，表示解析结果是null。
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);//如果第一个字符是'n'，则调用lept_parse_null函数来解析null值
        case '\0': return LEPT_PARSE_EXPECT_VALUE;//只含有空白
        default:   return LEPT_PARSE_INVALID_VALUE;//若值不是那三种字面值
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);//如果变量v的值不为NULL（空值），则断言为真，程序继续执行
    c.json = json;
    v->type = LEPT_NULL;//将v的type成员设置为LEPT_NULL
    lept_parse_whitespace(&c);//跳过JSON字符串中的空白字符
    return lept_parse_value(&c, v);//解析JSON字符串的值，并将解析结果存储在v中。函数返回解析结果
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
