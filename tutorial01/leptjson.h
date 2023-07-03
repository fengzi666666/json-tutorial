#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;
//声明枚举类型
typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,//只含有空白
    LEPT_PARSE_INVALID_VALUE,//若值不是那三种字面值
    LEPT_PARSE_ROOT_NOT_SINGULAR//若一个值之后，在空白之后还有其他字符
};//返回值是枚举值

int lept_parse(lept_value* v, const char* json);//解析 JSON函数  返回值是枚举值

lept_type lept_get_type(const lept_value* v);//获取其类型

#endif /* LEPTJSON_H__ */
