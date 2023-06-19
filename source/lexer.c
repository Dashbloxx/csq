#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "main.h"
#include "logger.h"

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

// Function to tokenize the input C code
void lex(const char* code) {
    int len = strlen(code);
    int pos = 0;
    token_t tokens[4096];
    int numTokens = 0;

    while (pos < len) {
        /* Skip whitespace... */
        while (isspace(code[pos])) {
            pos++;
        }

        /** @brief Check for specific types of tokens... */
        if (isalpha(code[pos]) || code[pos] == '_') {
            int start = pos;
            while (isalnum(code[pos]) || code[pos] == '_') {
                pos++;
            }

            int length = pos - start;
            char* lexeme = malloc(length + 1);
            strncpy(lexeme, code + start, length);
            lexeme[length] = '\0';

            token_t token;
            if (iskeyword(lexeme)) {
                token.type = TOKEN_TYPE_KEYWORD;
            } else {
                token.type = TOKEN_TYPE_IDENTIFIER;
            }
            strncpy(token.lexeme, lexeme, length + 1);
            tokens[numTokens++] = token;

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

            token_t token;
            token.type = TOKEN_TYPE_CONSTANT;
            strncpy(token.lexeme, lexeme, length + 1);
            tokens[numTokens++] = token;

            free(lexeme);
        }
        else if (code[pos] == '+' || code[pos] == '-' || code[pos] == '*' || code[pos] == '/') {
            token_t token;
            token.type = TOKEN_TYPE_OPERATOR;
            token.lexeme[0] = code[pos];
            token.lexeme[1] = '\0';
            tokens[numTokens++] = token;
            pos++;
        }
        else if (strchr(",;(){}[]", code[pos])) {
            token_t token;
            token.type = TOKEN_TYPE_SEPARATOR;
            token.lexeme[0] = code[pos];
            token.lexeme[1] = '\0';
            tokens[numTokens++] = token;
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

            token_t token;
            token.type = TOKEN_TYPE_STRING_LITERAL;
            strncpy(token.lexeme, lexeme, length + 1);
            tokens[numTokens++] = token;

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

            token_t token;
            token.type = TOKEN_TYPE_CHARACTER_LITERAL;
            strncpy(token.lexeme, lexeme, length + 1);
            tokens[numTokens++] = token;

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

            token_t token;
            token.type = TOKEN_TYPE_COMMENT;
            strncpy(token.lexeme, lexeme, length + 1);
            tokens[numTokens++] = token;

            free(lexeme);
        }
        else {
            token_t token;
            token.type = TOKEN_TYPE_UNKNOWN;
            token.lexeme[0] = code[pos];
            token.lexeme[1] = '\0';
            tokens[numTokens++] = token;
            pos++;
        }
    }

    /* Print out the tokens... */
    for (int i = 0; i < numTokens; i++) {
        printf("TOKEN TYPE: %d, TOKEN: %s\n", tokens[i].type, tokens[i].lexeme);
    }
}