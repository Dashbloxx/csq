#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parse.h"
#include "lexer.h"

int astgen(token_t **tokens, int *num_tokens, void *AST) {
    obj_t *objects = malloc(sizeof(obj_t) * 1024);
    int j = 0;
    bool was_a_storage_class_specifier_defined = false;
    bool was_a_type_modifier_defined = false;
    bool was_a_type_defined = false;
    bool is_type_a_struct = false;
    for (int i = 0; i <= *num_tokens; i++) {
        if (tokens[i]->type == TOKEN_TYPE_KEYWORD) {
            /* Handle storage classes... */
            if (strcmp(tokens[i]->lexeme, "extern") == 0) {
                j++;
                was_a_storage_class_specifier_defined = true;
                objects[j].storage_class = TOKEN_EXTERN;
            } else if (strcmp(tokens[i]->lexeme, "auto") == 0) {
                j++;
                was_a_storage_class_specifier_defined = true;
                objects[j].storage_class = TOKEN_AUTO;
            } else if (strcmp(tokens[i]->lexeme, "static") == 0) {
                j++;
                was_a_storage_class_specifier_defined = true;
                objects[j].storage_class = TOKEN_STATIC;
            } else if (strcmp(tokens[i]->lexeme, "register") == 0) {
                j++;
                was_a_storage_class_specifier_defined = true;
                objects[j].storage_class = TOKEN_REGISTER;
            }
            /* Handle type modifiers... */
            else if (strcmp(tokens[i]->lexeme, "short") == 0) {
                j++;
                was_a_type_modifier_defined = true;
                objects[j].storage_class = TOKEN_SHORT;
            } else if (strcmp(tokens[i]->lexeme, "long") == 0) {
                j++;
                was_a_type_modifier_defined = true;
                objects[j].storage_class = TOKEN_LONG;
            } else if (strcmp(tokens[i]->lexeme, "signed") == 0) {
                j++;
                was_a_type_modifier_defined = true;
                objects[j].storage_class = TOKEN_SIGNED;
            } else if (strcmp(tokens[i]->lexeme, "unsigned") == 0) {
                j++;
                was_a_type_modifier_defined = true;
                objects[j].storage_class = TOKEN_UNSIGNED;
            }
            /* Handle basic types... */
            else if (strcmp(tokens[i]->lexeme, "char") == 0) {
                j++;
                was_a_type_defined = true;
                objects[j].storage_class = TOKEN_CHAR;
            } else if (strcmp(tokens[i]->lexeme, "int") == 0) {
                j++;
                was_a_type_defined = true;
                objects[j].storage_class = TOKEN_INT;
            } else if (strcmp(tokens[i]->lexeme, "void") == 0) {
                j++;
                was_a_type_defined = true;
                objects[j].storage_class = TOKEN_VOID;
            }
        }
    }

    free(objects);
    return 0;
}