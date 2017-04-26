#ifndef SEMANTIC_H
#define SEMANTIC_H

struct semantic_type;

struct structure_field
{
    char* name; // 域的名字
    struct semantic_type *type; // 域的类型
    struct structure_field *next;
};

struct semantic_type
{
    enum { BASIC, ARRAY, STRUCTURE } kind;
    union
    {
        // basic type(INT or FLOAT)
        int basic;
        // 数组类型信息包括元素类型与数组大小构成
        struct { struct semantic_type *elem; int size; } array;
        // 结构体类型信息是一个链表
        struct structure_field *structure;
    } u;
};
#endif
