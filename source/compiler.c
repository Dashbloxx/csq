#include <stdlib.h>

#include "compiler.h"
#include "lexer.h"
#include "main.h"
#include "lexer.h"

/**
 *  @brief Compiles C² code
 *  
 *  @param input_buffer Pointer to buffer that contains code that is to be compiled
 *  @param output_buffer Pointer to buffer that contains compiled machine code
 *  @return Return code
 */
int compile(char *input_buffer, char *output_buffer) {
    token_t *token_buffer = malloc(sizeof(token_t) * BUFFER_SIZE);
    lex(input_buffer, token_buffer);
    free(token_buffer);
}