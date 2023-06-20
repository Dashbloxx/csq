#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "main.h"
#include "logger.h"

/**
 *  @brief Check if inputted string is a keyword or not...
 *  @param word pointer to string containing the actual string data...
 */
static int iskeyword(const char* word) {
    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 *  @brief Return token array generated from lexer (this)...
 *  @param code Pointer to string that contains C code...
 *  @param num_tokens Amount of tokens in the token array that is to be returned...
 */
token_t** lex(const char* code, int* num_tokens) {
    int len = strlen(code);
    int pos = 0;
    token_t** tokens = malloc(sizeof(token_t*) * len);
    *num_tokens = 0;

    while (pos < len) {
        while (isspace(code[pos])) {
            pos++;
        }

        if (isalpha(code[pos]) || code[pos] == '_') {
            int start = pos;
            while (isalnum(code[pos]) || code[pos] == '_') {
                pos++;
            }

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t* token = malloc(sizeof(token_t));
            if (iskeyword(lexeme)) {
                token->type = TOKEN_TYPE_KEYWORD;
            } else {
                token->type = TOKEN_TYPE_IDENTIFIER;
            }
            strncpy(token->lexeme, lexeme, length + 1);
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            free(lexeme);
        }
        else if (isdigit(code[pos])) {
            int start = pos;
            while (isdigit(code[pos])) {
                pos++;
            }

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_CONSTANT;
            strncpy(token->lexeme, lexeme, length + 1);
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            free(lexeme);
        }
        else if (code[pos] == '+' || code[pos] == '-' || code[pos] == '*' || code[pos] == '/') {
            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_OPERATOR;
            token->lexeme[0] = code[pos];
            token->lexeme[1] = '\0';
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            pos++;
        }
        else if (strchr(",;(){}[]", code[pos])) {
            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_SEPARATOR;
            token->lexeme[0] = code[pos];
            token->lexeme[1] = '\0';
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            pos++;
        }
        else if (code[pos] == '"') {
            int start = pos;
            pos++;
            while (code[pos] != '"' && pos < len) {
                pos++;
            }
            pos++;

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_STRING_LITERAL;
            strncpy(token->lexeme, lexeme, length + 1);
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            free(lexeme);
        }
        else if (code[pos] == '\'') {
            int start = pos;
            pos++;
            while (code[pos] != '\'' && pos < len) {
                pos++;
            }
            pos++;

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_CHARACTER_LITERAL;
            strncpy(token->lexeme, lexeme, length + 1);
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            free(lexeme);
        }
        else if (code[pos] == '/' && code[pos + 1] == '/') {
            int start = pos;
            pos += 2;
            while (code[pos] != '\n' && pos < len) {
                pos++;
            }

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_COMMENT;
            strncpy(token->lexeme, lexeme, length + 1);
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            free(lexeme);
        }
        else {
            token_t* token = malloc(sizeof(token_t));
            token->type = TOKEN_TYPE_UNKNOWN;
            token->lexeme[0] = code[pos];
            token->lexeme[1] = '\0';
            tokens[*num_tokens] = token;
            (*num_tokens)++;

            pos++;
        }
    }

    return tokens;
}

/**
 *  @brief De-allocate token array that is returned by lexer function...
 *  @param tokens Token array...
 *  @param num_tokens Amount of tokens in token array...
 */
void free_tokens(token_t** tokens, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        free(tokens[i]);
    }
    free(tokens);
}