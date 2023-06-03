#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "lexer.h"
#include "main.h"

int lex(char *input_buffer, token_t *output_buffer) {
    unsigned int input_length = strlen(input_buffer);
    unsigned int output_index = 0;

    for (unsigned int i = 0; i < input_length; i++) {
        if (strncmp(&input_buffer[i], "auto", 4) == 0) {
            output_buffer[output_index] = TOKEN_AUTO;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "const", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "double", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "float", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "int", 3) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 2;
        } else if (strncmp(&input_buffer[i], "short", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "struct", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "unsigned", 8) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "break", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "continue", 8) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "else", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "for", 3) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 2;
        } else if (strncmp(&input_buffer[i], "long", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "signed", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "switch", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "void", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "case", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "default", 7) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 6;
        } else if (strncmp(&input_buffer[i], "enum", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "goto", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "register", 8) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "sizeof", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "typedef", 7) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 6;
        } else if (strncmp(&input_buffer[i], "volatile", 8) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "char", 4) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "do", 2) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "extern", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "if", 2) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "return", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "static", 6) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "union", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "while", 5) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "!", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "\"", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "#", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "$", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "&", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "(", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ")", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "!=", 2) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "+", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ",", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "_", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "/", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ":", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ";", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "<", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "?", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "@", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "[", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "]", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "||", 2) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "^", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "-", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "`", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "{", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "}", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ">", 1) == 0) {
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 0;
        }
    }

    return output_index;
}