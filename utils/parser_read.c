#include "bool.h"
#include "symbol_pool.h"
#include <stdint.h>
#include <stdio.h>

typedef uint8_t OperationMode ;

enum {
    OP_DECLARE,
    OP_STORE,
    OP_LOAD,
    OP_ADD,
    OP_SUB,
    OP_CALL,
    OP_JUMP_IF_FALSE,
    OP_JUMP_IF_TRUE,
    OP_COMPARE,
    OP_RETURN,
    OP_UNKNOWN = 999
};


bool expect_keyword(Token token) {
    if (token.token_type != TOKEN_KEYWORD) {
        return false;
    }
    return true;
}

bool expect_operator(Token token) {
    if (token.token_type != TOKEN_OPERATOR) {
        return false;
    }
    return true;
}

bool expect_punctuation(Token token) {
    if (token.token_type != TOKEN_PUNCTUATION) {
        return false;
    }
    return true;
}

bool expect_identifier(Token token) {
    if (token.token_type != TOKEN_IDENTIFIER) {
        return false;
    }
    return true;
}

bool expect_string_literal(Token token) {
    if (token.token_type != TOKEN_LITERAL_STRING) {
        return false;
    }
    return true;
}

bool expect_int_literal(Token token) {
    if (token.token_type != TOKEN_LITERAL_INT) {
        return false;
    }
    return true;
}

bool expect_float_literal(Token token) {
    if (token.token_type != TOKEN_LITERAL_FLOAT) {
        return false;
    }
    return true;
}

bool expect_pre_type_var_declare(Token token) {
    if (expect_keyword(token) == false) {
        return false;
    }
    static uint8_t pre_type[5] = {CONST, STATIC, VOLATILE, REGISTER, EXTERN};
    uint8_t i;

    for (i=0; i<5; i++) {
        if (token.sub_token_type == pre_type[i]) {
            return true;
        }
    }

    return false;
}

bool expect_type(Token token) {
    if (expect_keyword(token) == false) {
        return false;
    }
    static uint8_t pre_type[7] = {CHAR,SHORT,INT,LONG,FLOAT,DOUBLE,VOID};
    uint8_t i;

    for (i=0; i<7; i++) {
        if (token.sub_token_type == pre_type[i]) {
            return true;
        }
    }

    return false;
}

bool expect_signable_type(Token token) {
    if (expect_keyword(token) == false) {
        return false;
    }
    static uint8_t pre_type[6] = {CHAR,SHORT,INT,LONG,FLOAT,DOUBLE};
    uint8_t i;

    for (i=0; i<6; i++) {
        if (token.sub_token_type == pre_type[i]) {
            return true;
        }
    }

    return false;

}

bool expect_sign(Token token) {
    if (expect_keyword(token) == false) {
        return false;
    }
    static uint8_t pre_type[2] = {SIGNED,UNSIGNED};
    uint8_t i;

    for (i=0; i<2; i++) {
        if (token.sub_token_type == pre_type[i]) {
            return true;
        }
    }

    return false;
}

bool expect_unknown_token(Token token) {
    if (token.token_type == TOKEN_UNKNOWN) {
        return true;
    }
    return false;
}

bool expect_assigment(Token token) {
    if (expect_operator(token) == false || token.sub_token_type != ASSIGN ) {
        return false;
    }
    return true;
}

bool expect_declaration(Token token) {
    if (expect_pre_type_var_declare(token) == true ||
        expect_sign(token) == true ||
        expect_signable_type(token) == true ||
        expect_type(token) == true
    ) {
        return true;
    }
    return false;
}

bool expect_semicolon(Token token) {
    if (expect_punctuation(token) == true) {
        return true;
    }
    return false;
}



void parser_read(Token token) {
    static OperationMode operation_mode = OP_DECLARE;
    static uint8_t counter_for_prev_assign = 0;
    const static Token emptyset = {0,TOKEN_UNKNOWN, IDENTIFIER_UNKNOWN,0};
    static Token current_token,prev_token = {0,TOKEN_UNKNOWN, IDENTIFIER_UNKNOWN,0};


    prev_token = current_token;
    current_token = token;

    if (counter_for_prev_assign <= 2) {
        counter_for_prev_assign++;
        return;
    }

    if (operation_mode == OP_DECLARE) {

        if (expect_pre_type_var_declare(prev_token) && expect_sign(current_token)) {
            return;
        }

        if (expect_pre_type_var_declare(prev_token) && expect_type(current_token)) {
            return;
        }

        if (expect_sign(prev_token) && expect_signable_type(current_token)) {
            return;
        }

        if (expect_signable_type(prev_token) && expect_unknown_token(current_token)) {
            return;
        }

        if (expect_type(prev_token) && expect_unknown_token(current_token)) {
            return;
        }

        if (expect_unknown_token(prev_token) && expect_assigment(current_token)) {
            return;
        }

        if (expect_assigment(prev_token) && expect_string_literal(current_token)) {
            return;
        }
        if (expect_assigment(prev_token) && expect_int_literal(current_token)) {
            return;
        }
        if (expect_assigment(prev_token) && expect_float_literal(current_token)) {
            return;
        }

        if (expect_string_literal(prev_token) && expect_semicolon(current_token)) {
            current_token = emptyset;
            prev_token = emptyset;
            counter_for_prev_assign = 0;
            return;
        }
        if (expect_int_literal(prev_token) && expect_semicolon(current_token)) {
            current_token = emptyset;
            prev_token = emptyset;
            counter_for_prev_assign = 0;
            return;
        }
        if (expect_float_literal(prev_token) && expect_semicolon(current_token)) {
            current_token = emptyset;
            prev_token = emptyset;
            counter_for_prev_assign = 0;
            return;
        }


        if (expect_unknown_token(prev_token) && expect_semicolon(token)) {
            current_token = emptyset;
            prev_token = emptyset;
            counter_for_prev_assign = 0;
            return;
        }

    }

    if (expect_declaration(token)) {
        printf("Declaration are only allowed before operation");
        return;
    }

};
