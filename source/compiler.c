#include <stdlib.h>
#include <stdio.h>

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
    int num_tokens = 0;
    token_t **tokens = lex(input_buffer, &num_tokens);
    
    for (int i = 0; i < num_tokens; i++) {
        printf("TOKEN ID: %d, TOKEN VALUE: %s\n", tokens[i]->type, tokens[i]->lexeme);
    }

    free_tokens(tokens, num_tokens);
}