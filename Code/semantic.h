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
        struct { struct structure_field *field; char *name; } structure;
    } u;
};

struct variable_symbol_table_entry {
    char *name;
    struct semantic_type *type;
    int line_no;
};

struct function_symbol_table_entry {
    // function name
    char *name;
    // number of arguments
    int argc;
    // type of args, it's an array
    struct semantic_type *args;
    struct semantic_type *return_type;
    int line_no;
};

struct structure_symbol_table_entry {
    // name should be the same as type->u.strucure.name
    char *name;
    struct semantic_type *type;
    int line_no;
};

int check_semantics(struct syntax_node *root);
#endif
