#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "compiler.h"
#include "main.h"

int main(int argc, const char *argv[]) {
    FILE *input_file_pointer, *output_file_pointer;
    char *input_file_contents, *output_file_contents;
    
    input_file_contents = malloc(BUFFER_SIZE);
    output_file_contents = malloc(BUFFER_SIZE);
    
    if(argc != 3) {
        sendf(stderr, LOG_ERROR, "Usage: csq <file.csq> <output.o>");
        return -1;
    }

    input_file_pointer = fopen(argv[1], "r");
    if (input_file_pointer == NULL) {
        sendf(stderr, LOG_ERROR, "Failed to open %s for reading...\n", argv[1]);
        return -1;
    }

    fread(input_file_contents, sizeof(char), BUFFER_SIZE, input_file_pointer);

    if(compile(input_file_contents, output_file_contents) != 0) {
        sendf(stderr, LOG_ERROR, "Failed to compile code...\n");
        free(input_file_contents);
        free(output_file_contents);
        return -1;
    }

    output_file_pointer = fopen(argv[2], "w");
    if (output_file_pointer == NULL) {
        sendf(stderr, LOG_ERROR, "Failed to open %s for writing...\n", argv[2]);
        return -1;
    }

    fwrite(output_file_contents, sizeof(char), strlen(output_file_contents), output_file_pointer);

    free(input_file_contents);
    free(output_file_contents);
    fclose(input_file_pointer);
    fclose(output_file_pointer);

    return 0;
}