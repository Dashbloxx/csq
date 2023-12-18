#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "string.h"
#include "vector.h"
#include "lex.h"

#ifdef _WIN32
#define ENDL "\r\n"
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
#define ENDL "\n"
#endif

FILE *fileitem = NULL;
const char *filename = NULL;
size_t filesize = 0;
char *contents = NULL;

int main(int argc, const char *argv[])
{
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "--file") == 0)
		{
			if(i + 1 < argc)
			{
				filename = argv[i + 1];
			}
			else
			{
				fprintf(stderr, "error: The flag `--file` has been specified, however no file was specified after it." ENDL);
				exit(EXIT_FAILURE);
			}
		}
	}

	fileitem = fopen(filename, "r");

	if(fileitem == NULL)
	{
		fprintf(stderr, "error: Failed to open `%s` for reading!" ENDL, filename);
		
		exit(EXIT_FAILURE);
	}

	fseek(fileitem, 0, SEEK_END);
	filesize = ftell(fileitem);
	rewind(fileitem);

	contents = (char *)malloc(filesize + 1);

	if(contents == NULL)
	{
		fprintf(stderr, "error: Memory allocation failed!" ENDL);
		fclose(fileitem);

		exit(EXIT_FAILURE);
	}

	size_t bytes_read = fread(contents, sizeof(char), filesize, fileitem);

	if (bytes_read != filesize)
	{
		fprintf(stderr, "error: Failed to read the entire file!" ENDL);
		free(contents);
		fclose(fileitem);

		exit(EXIT_FAILURE);
	}

	contents[filesize] = '\0';

	string_t source, assembly;
	string_create(&source);
	string_create(&assembly);
	string_copy(&source, contents);

	vector_t tokens;
	vector_create(&tokens);

	int status = lex(&source, &tokens);
	if(status != 0)
	{
		string_delete(&source);
		string_delete(&assembly);
		vector_free(&tokens);

		fprintf(stderr, "error: Lexer returned a non-0 value!" ENDL);
	}

	string_delete(&source);
	string_delete(&assembly);
	vector_free(&tokens);

	free(contents);
	fclose(fileitem);

	exit(EXIT_SUCCESS);
}