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
        }
    }

    return output_index;
}