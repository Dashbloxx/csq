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
        /*
         *  Keywords can have spaces between them, or parenthesis besides them, or parenthesis and an asterisk to the right of them. This is
         *  is why we need to have more complex parsing for keywords...
         */
        if ((strncmp(&input_buffer[i], "extern", 6) == 0) && (input_buffer[i + 7] == ' ') && ((input_buffer[i - 1] == ' ') || (input_buffer[i - 1] == '\t'))) {
            sendf(stdout, LOG_DEBUG, "Detected `auto` token in position %d of `input_buffer`.\n", i);
            output_buffer[output_index] = TOKEN_AUTO;
            output_index++;
            i += 3;
        }
    }

    return output_index;
}