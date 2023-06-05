#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "lexer.h"
#include "main.h"
#include "logger.h"

int lex(char *input_buffer, token_t *output_buffer) {
    if(input_buffer == NULL) {
        sendf(stderr, LOG_ERROR, "Input buffer is set to NULL...\n");
        return -1;
    } if(output_buffer == NULL) {
        sendf(stderr, LOG_ERROR, "Output buffer (aka. token buffer or lexer output) is set to NULL...\n");
        return -1;
    }

    unsigned int input_length = strlen(input_buffer);
    unsigned int output_index = 0;

    for (unsigned int i = 0; i <= input_length; i++) {
        if ((strncmp(&input_buffer[i], "auto", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `auto` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_AUTO;
            output_index++;
            i += 3;
        } else if ((strncmp(&input_buffer[i], "const", 5) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 6] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `const` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CONST;
            output_index++;
            i += 4;
        } else if ((strncmp(&input_buffer[i], "double", 6) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 7] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `double` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_DOUBLE;
            output_index++;
            i += 5;
        } else if ((strncmp(&input_buffer[i], "float", 5) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 6] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `float` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_FLOAT;
            output_index++;
            i += 4;
        } else if ((strncmp(&input_buffer[i], "int", 3) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 4] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `int` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_INT;
            output_index++;
            i += 2;
        } else if ((strncmp(&input_buffer[i], "short", 5) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 6] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `short` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SHORT;
            output_index++;
            i += 4;
        } else if ((strncmp(&input_buffer[i], "struct", 6) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 7] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `struct` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_STRUCT;
            output_index++;
            i += 5;
        } else if ((strncmp(&input_buffer[i], "unsigned", 8) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 9] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `unsigned` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_UNSIGNED;
            output_index++;
            i += 7;
        } else if ((strncmp(&input_buffer[i], "break", 5) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 6] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `break` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_BREAK;
            output_index++;
            i += 4;
        } else if ((strncmp(&input_buffer[i], "continue", 8) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 9] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `continue` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CONTINUE;
            output_index++;
            i += 7;
        } else if ((strncmp(&input_buffer[i], "else", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `else` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_ELSE;
            output_index++;
            i += 3;
        } else if ((strncmp(&input_buffer[i], "for", 3) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 4] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `for` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_FOR;
            output_index++;
            i += 2;
        } else if ((strncmp(&input_buffer[i], "long", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `long` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_LONG;
            output_index++;
            i += 3;
        } else if ((strncmp(&input_buffer[i], "signed", 6) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 7] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `signed` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SIGNED;
            output_index++;
            i += 5;
        } else if ((strncmp(&input_buffer[i], "switch", 6) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 7] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `switch` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SWITCH;
            output_index++;
            i += 5;
        } else if ((strncmp(&input_buffer[i], "void", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `void` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_VOID;
            output_index++;
            i += 3;
        } else if ((strncmp(&input_buffer[i], "case", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `case` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CASE;
            output_index++;
            i += 3;
        } else if ((strncmp(&input_buffer[i], "default", 7) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 8] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `default` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_DEFAULT;
            output_index++;
            i += 6;
        } else if ((strncmp(&input_buffer[i], "enum", 4) == 0) && (input_buffer[i - 1] == ' ') && (input_buffer[i + 5] == ' ')) {
            sendf(stdout, LOG_DEBUG, "Detected `enum` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_ENUM;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "goto", 4) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `goto` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_GOTO;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "register", 8) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `register` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_REGISTER;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "sizeof", 6) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `sizeof` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SIZEOF;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "typedef", 7) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `typedef` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_TYPEDEF;
            output_index++;
            i += 6;
        } else if (strncmp(&input_buffer[i], "volatile", 8) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `volatile` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_VOLATILE;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "char", 4) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `char` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CHAR;
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "do", 2) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `do` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_DO;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "extern", 6) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `extern` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_EXTERN;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "if", 2) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `if` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_IF;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "return", 6) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `return` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_RETURN;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "static", 6) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `static` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_STATIC;
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "union", 5) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `union` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_UNION;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "while", 5) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `while` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_WHILE;
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "!", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `!` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_EXCLAMATION_POINT;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "\"", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `\"` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_QUOTE;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "#", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `#` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_HASHTAG;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "$", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `$` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_DOLLAR_SYMBOL;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "&", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `&` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_AMPERSAND;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "(", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `(` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_OPENING_PARENTHESIS;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ")", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `)` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CLOSING_PARENTHESIS;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "!=", 2) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `!=` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_NOT_EQUAL_TO;
            output_index++;
            i += 1;
        } else if (strncmp(&input_buffer[i], "+", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `+` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_PLUS;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ",", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `,` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_COMMA;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "_", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `_` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_UNDERSCORE;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "/", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `/` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SLASH;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ":", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `:` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_COLON;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ";", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `;` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SEMICOLON;
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "<", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `<` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_SMALLER_THAN;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "?", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `?` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_QUESTION_MARK;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "@", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `@` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_AT;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "[", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `[` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_OPENING_SQUARE_BRACKET;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "]", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `]` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CLOSING_SQUARE_BRACKET;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "||", 2) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `||` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_OR;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "^", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `^` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CARET;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "-", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `-` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_DASH;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "`", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected ``` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_ARMENIAN_COMMA;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "{", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `{` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_OPENING_BRACKET;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], "}", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `}` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_CLOSING_BRACKET;
            output_index++;
            i += 0;
        } else if (strncmp(&input_buffer[i], ">", 1) == 0) {
            sendf(stdout, LOG_DEBUG, "Detected `>` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_BIGGER_THAN;
            output_index++;
            i += 0;
        }
    }

    return output_index;
}