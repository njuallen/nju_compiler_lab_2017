enum token_value {
    INT = 1, FLOAT, ID, SEMI, 
    COMMA, ASSIGNOP, RELOP, PLUS, MINUS, 
    STAR, DIV, AND, OR, DOT, 
    NOT, TYPE, LP, RP, LB, 
    RB, LC, RC, STRUCT, RETURN, 
    IF, ELSE, WHILE,
    INVALID
};

struct token {
    /* value of the token, see enum token_value */
    int value;
    const char *name;
};

extern struct token tokens[];
