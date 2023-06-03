#include <stddef.h>
#include <stdint.h>

#include "lexer.h"
#include "main.h"

int lex(char *input_buffer, token_t *output_buffer) {
    uint input_length = strlen(input_buffer);
    uint output_index = 0;

    for (uint i = 0; i < input_length; i++) {
        if (strncmp(&input_buffer[i], "auto", 4) == 0) {
            output_buffer[output_index].type = TOKEN_AUTO;
            strncpy(output_buffer[output_index].raw, "auto", 5);
            output_index++;
            i += 3;
        } else if (strncmp(&input_buffer[i], "const", 5) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "const", 6);
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "double", 6) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "double", 7);
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "float", 5) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "float", 6);
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "int", 3) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "int", 4);
            output_index++;
            i += 2;
        } else if (strncmp(&input_buffer[i], "short", 5) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "short", 6);
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "struct", 6) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "short", 7);
            output_index++;
            i += 5;
        } else if (strncmp(&input_buffer[i], "unsigned", 8) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "short", 9);
            output_index++;
            i += 7;
        } else if (strncmp(&input_buffer[i], "break", 5) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "short", 6);
            output_index++;
            i += 4;
        } else if (strncmp(&input_buffer[i], "continue", 8) == 0) {
            output_buffer[output_index].type = TOKEN_CONST;
            strncpy(output_buffer[output_index].raw, "short", 9);
            output_index++;
            i += 7;
        }
    }

    return output_index;
}