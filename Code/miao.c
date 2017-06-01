
void translate_ExtDecList(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *var_dec = child_1(root);
    translate_VarDec(var_dec, type);

    // ExtDecList : VarDec COMMA ExtDecList
    if(var_dec->next)
        translate_ExtDecList(child_3(root), type);
}

struct semantic_type *translate_Specifier(struct syntax_node *root) {
    struct semantic_type *ret = NULL;
    if(child_1(root)->node_type == TYPE) {
        // Specifier : TYPE
        ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = BASIC;
        if(!strcmp(child_1(root)->value.string_value, "int"))
            ret->u.basic = INT;
        else
            ret->u.basic = FLOAT;
    }
    else {
        // Specifier : StructSpecifier
        ret = translate_StructSpecifier(child_1(root));
    }
    return ret;
}

char *translate_OptTag(struct syntax_node *root) {
    if(!root->is_empty)
        // copy it, in case we free the syntax tree later
        return Strdup(root->child->value.string_value);
    else {
        // anonymous structure, we give it a unique name
        static int counter = 0;
        char buf[100];
        sprintf(buf, "<struct>_%d", counter++);
        return Strdup(buf);
    }
}

struct semantic_type *translate_StructSpecifier(struct syntax_node *root) {

    struct structure_symbol_table_entry *old = NULL;

    struct structure_symbol_table_entry *entry = 
        Calloc(1, sizeof(struct structure_symbol_table_entry));
    entry->line_no = child_1(root)->line_no;

    if(child_2(root)->node_type == OptTag) {
        // STRUCT OptTag LC DefList RC
        /* we are defining a new structure
         * check for redefinition
         */
        entry->name = translate_OptTag(child_2(root));
        old = hash_table_search(structure_symbol_table, entry);
        if(old) {
            semantic_error(DUPLICATE_STRUCTURE, entry->line_no, entry->name);
            return NULL;
        }

        struct semantic_type *ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = STRUCTURE;
        ret->u.structure.name = Strdup(entry->name);

        create_scope(STRUCTURE_SCOPE);

        // field definition
        translate_DefList(child_4(root));

        /* the fields are chained in the inner most scope
         * we build the structure fields according to them
         */
        struct structure_field *curr_field = NULL;
        struct hash_node **top = cstack_top(variable_scopes);
        struct hash_node *curr = *top;
        while(curr) {
            struct variable_symbol_table_entry *entry = curr->elem;
            struct structure_field *field = Calloc(1, sizeof(struct structure_field));
            field->name = Strdup(entry->name);
            field->type = entry->type;
            field->next = NULL;
            if(!curr_field)
                ret->u.structure.field = curr_field = field;
            else {
                curr_field->next = field;
                curr_field = field;
            }
            curr = curr->brother;
        }

        delete_scope();
        /* structure type has been built
         * we need to insert it into structure_symbol_table_entry
         */
        entry->type = ret;
        hash_table_insert(structure_symbol_table, entry);
        return ret;
    }
    else {
        // STRUCT Tag
        /* this is not a structure definition
         * we are using a structure
         * it must be defined
         */
        entry->name = Strdup(child_2(root)->child->value.string_value);
        old = hash_table_search(structure_symbol_table, entry);
        if(!old) {
            semantic_error(UNDEFINED_STRUCTURE, entry->line_no, entry->name);
            return NULL;
        }
        else
            return old->type;
    }
}

void translate_DefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        translate_Def(child_1(root));
        translate_DefList(child_2(root));
    }
}

void translate_Def(struct syntax_node *root) {
    struct syntax_node *specifier = child_1(root);
    struct semantic_type *type = translate_Specifier(specifier);
    // ExtDef : Specifier DecList SEMI
    if(child_2(root)->node_type == DecList) {
        translate_DecList(child_2(root), type);
    }
}

void translate_DecList(struct syntax_node *root, struct semantic_type *type) {
    translate_Dec(child_1(root), type);
    if(child_1(root)->next) {
        // DecList : Dec COMMA DecList
        translate_DecList(child_3(root), type);
    }
}

void translate_Dec(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *var_dec = child_1(root);
    struct semantic_type *t = translate_VarDec(var_dec, type);

    if(var_dec->next) {
        // Dec : VarDec ASSIGNOP Exp
        if(get_inner_most_scope_type() == STRUCTURE_SCOPE) {
            sprintf(msg_buffer, "Structure field initialized at definition");
            semantic_error(STRUCTURE_FIELD_ERROR, child_2(root)->line_no, msg_buffer);
        }
        else {
            struct semantic_type *exp_type = NULL;
            int exp_is_left_value = 0;
            exp_type = translate_Exp(child_3(root), &exp_is_left_value);
            if(!t || !exp_type ||
                    !compare_semantic_type(t, exp_type) ||
                    t->kind == ARRAY) {
                // only basic and structure types can be assigned directly
                semantic_error(ASSIGNMENT_TYPE_MISMATCH, child_2(root)->line_no);
            }
        }
    }
}

struct semantic_type *translate_VarDec(struct syntax_node *root, struct semantic_type *type) {
    if(child_1(root)->node_type == ID) {
        // VarDec : ID
        struct syntax_node *id = child_1(root);
        struct variable_symbol_table_entry *entry = 
            Calloc(1, sizeof(struct variable_symbol_table_entry));
        entry->name = Strdup(id->value.string_value);
        entry->type = type;
        entry->line_no = id->line_no;
        struct hash_node *old = 
            search_inner_most_variable_scope(entry->name);
        if(old) {
            int curr_scope_type = get_inner_most_scope_type();
            if(curr_scope_type == VARIABLE_SCOPE)
                // variable redefinition
                semantic_error(REDEFINED_VARIABLE, entry->line_no, entry->name);
            else {
                // structure field redefinition
                sprintf(msg_buffer, "Redefined field \"%s\"", entry->name);
                semantic_error(STRUCTURE_FIELD_ERROR, entry->line_no, msg_buffer);
            }
        }
        else {
            // insert into symbol table
            struct hash_node *curr = hash_table_insert(variable_symbol_table, entry);
            // insert into current scope
            insert_into_inner_most_variable_scope(curr);
        }
        return type;
    }
    else {
        // VarDec : VarDec LB INT RB
        // array type
        struct semantic_type *ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = ARRAY;
        ret->u.array.elem = type;
        ret->u.array.size = child_3(root)->value.int_value;
        return translate_VarDec(child_1(root), ret);
    }
}

void translate_CompSt(struct syntax_node *root, struct semantic_type *function_return_type) {
    // CompSt : LC DefList StmtList RC
    translate_DefList(child_2(root));
    translate_StmtList(child_3(root), function_return_type);
}

    void translate_StmtList(struct syntax_node *root, struct semantic_type *function_return_type) {
        if(!root->is_empty) {
            // StmtList : Stmt StmtList
            translate_Stmt(child_1(root), function_return_type);
            translate_StmtList(child_2(root), function_return_type);
        }
    }

    void translate_Stmt(struct syntax_node *root, struct semantic_type *function_return_type) {
        int is_left_value = 0;
        struct semantic_type *exp_type = NULL;
        switch(child_1(root)->node_type) {
            case Exp:
                // Stmt : Exp SEMI
                translate_Exp(child_1(root), &is_left_value);
                break;
            case CompSt:
                // Stmt : CompSt
                create_scope(VARIABLE_SCOPE);
                translate_CompSt(child_1(root), function_return_type);
                delete_scope();
                break;
            case RETURN:
                // Stmt : RETURN Exp SEMI
                exp_type = translate_Exp(child_2(root), &is_left_value);
                if(!compare_semantic_type(function_return_type, exp_type))
                    semantic_error(RETURN_TYPE_MISMATCH, child_1(root)->line_no);
                break;
            case IF:
                // Stmt : IF LP Exp RP Stmt
                // Stmt : IF LP Exp RP Stmt ELSE Stmt
                exp_type = translate_Exp(child_3(root), &is_left_value);
                /* condition must be of basic type
                 * float type is OK, I have tried with clang
                 * when float value != 0.0, it's true
                 * else it's false.
                 * Just like with integer
                 */
                if(!exp_type || exp_type->kind != BASIC ||
                        exp_type->u.basic != INT) {
                    sprintf(msg_buffer, "\"if\" expects condition of integer type");
                    semantic_error(OPERANDS_TYPE_MISMATCH, 
                            child_1(root)->line_no, msg_buffer);
                }
                translate_Stmt(child_5(root), function_return_type);
                if(num_child(root) > 5)
                    translate_Stmt(child_7(root), function_return_type);
                break;
            case WHILE:
                // Stmt : WHILE LP Exp RP Stmt
                exp_type = translate_Exp(child_3(root), &is_left_value);
                if(!exp_type || exp_type->kind != BASIC ||
                        exp_type->u.basic != INT) {
                    sprintf(msg_buffer, "\"while\" expects condition of integer type");
                    semantic_error(OPERANDS_TYPE_MISMATCH, 
                            child_1(root)->line_no, msg_buffer);
                }
                translate_Stmt(child_5(root), function_return_type);
                break;
            default:
                break;
        }
    }

    /* return the type of the expresession
     * is_left_value is set to indicate the left/right value type of the expresession
     */
    struct semantic_type *translate_Exp(struct syntax_node *root, int *is_left_value) {
        struct semantic_type *ret = NULL;
        struct variable_symbol_table_entry *entry = NULL, *old = NULL;
        struct semantic_type *exp1_type = NULL, *exp2_type = NULL;
        int exp1_is_left_value, exp2_is_left_value;

        switch(child_1(root)->node_type) {
            case Exp:
                exp1_type = translate_Exp(child_1(root), &exp1_is_left_value);
                switch(child_2(root)->node_type) {
                    case PLUS:
                    case MINUS:
                    case STAR:
                    case DIV:
                    case RELOP:
                        /* Exp arithmetic/comparison operator Exp
                         * Exp must be of basic type
                         *
                         * Exp : Exp PLUS Exp
                         * Exp : Exp MINUS Exp
                         * Exp : Exp STAR Exp
                         * Exp : Exp DIV Exp
                         * Exp : Exp RELOP Exp
                         */
                        exp2_type = translate_Exp(child_3(root), &exp2_is_left_value);
                        if(!exp1_type || !exp2_type || exp1_type->kind != BASIC || 
                                exp2_type->kind != BASIC || 
                                exp1_type->u.basic != exp2_type->u.basic) {
                            sprintf(msg_buffer, "arithmetic and relational operators expect operand of basic type");
                            semantic_error(OPERANDS_TYPE_MISMATCH, 
                                    child_2(root)->line_no, msg_buffer);
                            ret = NULL;
                        }
                        else {
                            if(child_2(root)->node_type == RELOP) {
                                ret = Calloc(1, sizeof(struct semantic_type));
                                ret->kind = BASIC;
                                ret->u.basic = INT;
                            }
                            else
                                ret = exp1_type;
                        }
                        *is_left_value = 0;
                        break;
                    case AND:
                    case OR:
                        /*
                         * Exp : Exp AND Exp
                         * Exp : Exp OR Exp
                         */
                        exp2_type = translate_Exp(child_3(root), &exp2_is_left_value);
                        if(!exp1_type || !exp2_type || exp1_type->kind != BASIC || 
                                exp2_type->kind != BASIC || 
                                exp1_type->u.basic != INT ||
                                exp2_type->u.basic != INT) {
                            sprintf(msg_buffer, "logical operators expect operand of basic type");
                            semantic_error(OPERANDS_TYPE_MISMATCH, 
                                    child_2(root)->line_no, msg_buffer);
                            ret = NULL;
                        }
                        else
                            ret = exp1_type;
                        *is_left_value = 0;
                        break;
                    case ASSIGNOP:
                        // Exp : Exp ASSIGNOP Exp
                        exp2_type = translate_Exp(child_3(root), &exp2_is_left_value);
                        if(!exp1_is_left_value) {
                            semantic_error(NOT_LEFT_VALUE, child_2(root)->line_no);
                            ret = NULL;
                        }else if(!exp1_type || !exp2_type ||
                                !compare_semantic_type(exp1_type, exp2_type) ||
                                exp1_type->kind == ARRAY) {
                            // only basic and structure types can be assigned directly
                            semantic_error(ASSIGNMENT_TYPE_MISMATCH, child_2(root)->line_no);
                            ret = NULL;
                        }
                        else
                            ret = exp1_type;
                        *is_left_value = 0;
                        break;
                    case LB:
                        // array
                        // Exp : Exp LB Exp RB
                        exp2_type = translate_Exp(child_3(root), &exp2_is_left_value);
                        if(!exp1_type || exp1_type->kind != ARRAY) {
                            semantic_error(NOT_AN_ARRAY, child_2(root)->line_no);
                            ret = NULL;
                        }
                        else {
                            if(!exp2_type || exp2_type->kind != BASIC || 
                                    exp2_type->u.basic != INT)
                                semantic_error(ARRAY_INDEX_NOT_INTEGER, child_2(root)->line_no);
                            ret = exp1_type->u.array.elem;
                        }
                        *is_left_value = 1;
                        break;
                    case DOT:
                        // structure
                        // Exp : Exp DOT ID
                        if(!exp1_type || exp1_type->kind != STRUCTURE) {
                            semantic_error(NOT_A_STRUCTURE, child_2(root)->line_no);
                            ret = NULL;
                        }
                        else {
                            // check whether this field exists
                            struct structure_field *field = exp1_type->u.structure.field;
                            int found = 0;
                            while(field) {
                                if(!strcmp(field->name, child_3(root)->value.string_value)) {
                                    found = 1;
                                    break;
                                }
                                field = field->next;
                            }
                            if(!found) {
                                semantic_error(NON_EXISTEND_FIELD, child_2(root)->line_no, 
                                        child_3(root)->value.string_value);
                                ret = NULL;
                            }
                            else
                                ret = field->type;
                        }
                        *is_left_value = 1;
                        break;
                    default:
                        break;
                }
                break;
            case LP:
                // Exp : LP Exp RP
                exp1_type = translate_Exp(child_2(root), &exp1_is_left_value);
                ret = exp1_type;
                *is_left_value = exp1_is_left_value;
                break;
            case MINUS:
                // Exp : NOT Exp
                exp1_type = translate_Exp(child_2(root), &exp1_is_left_value);
                if(!exp1_type || exp1_type->kind != BASIC) {
                    sprintf(msg_buffer, "arithmetic operators expect operand of basic type");
                    semantic_error(OPERANDS_TYPE_MISMATCH, 
                            child_1(root)->line_no, msg_buffer);
                    ret = NULL;
                }
                else
                    ret = exp1_type;
                *is_left_value = 0;
                break;
            case NOT:
                // Exp : NOT Exp
                exp1_type = translate_Exp(child_2(root), &exp1_is_left_value);
                if(!exp1_type || exp1_type->kind != BASIC ||
                        exp1_type->u.basic != INT) {
                    sprintf(msg_buffer, "logical operators expect operand of basic type");
                    semantic_error(OPERANDS_TYPE_MISMATCH, 
                            child_1(root)->line_no, msg_buffer);
                    ret = NULL;
                }
                else
                    ret = exp1_type;
                *is_left_value = 0;
                break;
            case ID:
                if(num_child(root) > 1) {
                    // function call
                    struct function_symbol_table_entry *entry = 
                        Calloc(1, sizeof(struct function_symbol_table_entry));
                    entry->name = Strdup(child_1(root)->value.string_value);
                    entry->line_no = child_1(root)->line_no;
                    struct function_symbol_table_entry *old = NULL;
                    // check whether this function has been defined
                    old = hash_table_search(function_definition_symbol_table, entry);

                    // if not defined check whether this function has been declared
                    if(!old)
                        old = hash_table_search(function_declaration_symbol_table, entry);

                    if(!old) {
                        // check whether it's a variable
                        struct variable_symbol_table_entry *e = 
                            Calloc(1, sizeof(struct variable_symbol_table_entry));
                        e->name = Strdup(child_1(root)->value.string_value);
                        e->line_no = child_1(root)->line_no;
                        struct variable_symbol_table_entry *v = NULL;
                        v = hash_table_search(variable_symbol_table, entry);
                        if(v)
                            // use "()" with variables
                            semantic_error(NOT_A_FUNCTION, entry->line_no, entry->name);
                        else
                            // we have never seen this name
                            semantic_error(UNDEFINED_FUNCTION, entry->line_no, entry->name);
                        ret = NULL;
                    }
                    else {
                        // check for arguments
                        int argc = 0;
                        struct semantic_type **arg_types = NULL;
                        if(child_3(root)->node_type == Args) {
                            // function call with arguments
                            // Exp : ID LP Args RP
                            arg_types = translate_Args(child_3(root), &argc);
                        }
                        if(argc != old->argc)
                            goto function_parameter_mismatch;
                        for(int i = 0; i < argc; i++)
                            if(!compare_semantic_type(arg_types[i], old->args[i]))
                                goto function_parameter_mismatch;

                        goto function_parameter_match;

function_parameter_mismatch:
                        semantic_error(FUNCTION_TYPE_MISMATCH, entry->line_no, entry->name);
function_parameter_match:
                        ret = old->return_type;
                    }
                    *is_left_value = 0;
                }
                else {
                    /* simply a variable
                     * we look it up in the variable_symbol_table
                     */
                    entry = Calloc(1, sizeof(struct variable_symbol_table_entry));
                    entry->name = Strdup(child_1(root)->value.string_value);
                    entry->line_no = child_1(root)->line_no;
                    old = hash_table_search(variable_symbol_table, entry);
                    if(!old) {
                        semantic_error(UNDEFINED_VARIABLE, entry->line_no, entry->name);
                        ret = NULL;
                    }
                    else
                        ret = old->type;
                    *is_left_value = 1;
                }
                break;
            case INT:
            case FLOAT:
                // Exp : INT
                // Exp : FLOAT
                ret = Calloc(1, sizeof(struct semantic_type));
                ret->kind = BASIC;
                ret->u.basic = child_1(root)->node_type;
                *is_left_value = 0;
                break;
            default:
                break;
        }
        return ret;
    }

    struct semantic_type **translate_Args(struct syntax_node *root, int *argc) {
        int is_left_value = 0;
        struct semantic_type *exp_type = translate_Exp(child_1(root), &is_left_value);
        struct semantic_type **ret = NULL, **child_ret = NULL;
        if(num_child(root) > 1) {
            // Args : Exp COMMA Args
            int count = 0;
            child_ret = translate_Args(child_3(root), &count);
            *argc = count + 1;
            ret = Calloc(*argc, sizeof(struct semantic_type *));
            memcpy(&ret[1], child_ret, count * sizeof(struct semantic_type *));
        }
        else {
            // Args : Exp
            *argc = 1;
            ret = Calloc(*argc, sizeof(struct semantic_type *));
        }
        ret[0] = exp_type;
        return ret;
    }
