#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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

	

	free(contents);
	fclose(fileitem);

	exit(EXIT_SUCCESS);
}