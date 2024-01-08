#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "string.h"
#include "vector.h"
#include "lex.h"
#include "endl.h"

/*
 *	These variables are for later handling the source code's file input and
 *	output.
 *	fileitem => The file handle representing the source code file.
 *	filename => The filename of the source code file.
 *	filesize => The size of the source code file (in bytes).
 *	contents => The contents of the source code file.
 */
FILE *fileitem = NULL;
const char *filename = NULL;
size_t filesize = 0;
char *contents = NULL;

int main(int argc, const char *argv[])
{
	/* Loop for all command-line arguments. */
	for(int i = 0; i < argc; i++)
	{
		/*
		 *	If we run across `--file`, check if there's another argument right
		 *	after the `--file` argument, and if there is, let's obtain that and
		 *	set `filename` to point to the argument right after `--file`.
		 *	To clarify, the argument that goes after `--file` is the string
		 *	representing the filename of the file containing the source code to
		 *	be compiled.
		 */
		if(strcmp(argv[i], "--file") == 0)
		{
			if(i + 1 < argc)
			{
				filename = argv[i + 1];
			}
			else
			{
				/*
				 *	If there's no argument available right after `--file`, then
				 *	let's "throw an exception".
				 */
				fprintf(stderr, "error: The flag `--file` has been specified, however no file was specified after it." ENDL);
				exit(EXIT_FAILURE);
			}
		}
	}

	/* Open the file containing the source code. */
	fileitem = fopen(filename, "r");

	/*
	 *	If the file handle is still NULL after calling the function to open it,
	 *	then "throw an exception".
	 */
	if(fileitem == NULL)
	{
		fprintf(stderr, "error: Failed to open `%s` for reading!" ENDL, filename);
		exit(EXIT_FAILURE);
	}

	/* Let's seek our "file cursor" to the start of the file. */
	fseek(fileitem, 0, SEEK_END);

	/* Obtain the filesize of the file & rewind. */
	filesize = ftell(fileitem);
	rewind(fileitem);

	/*
	 *	Allocate enough memory, so that we can copy the file's contents to the
	 *	newly-allocated memory. We also allocate one more byte at the end so
	 *	that we can stick in a NULL terminator.
	 */
	contents = (char *)malloc(filesize + 1);

	/*
	 *	If our memory pointer is NULL, it means the memory allocation failed,
	 *	therefore we must "throw an exception".
	 */
	if(contents == NULL)
	{
		fprintf(stderr, "error: Memory allocation failed!" ENDL);

		/*
		 *	Let's also make sure to end our access to the source code file
		 *	before exiting.
		 */
		fclose(fileitem);
		exit(EXIT_FAILURE);
	}

	/*
	 *	Let's read the contents of the source code file into our newly
	 *	allocated memory. We also store the bytes read, and you'll see
	 *	why we did it soon.
	 */
	size_t bytes_read = fread(contents, sizeof(char), filesize, fileitem);

	/*
	 *	If the bytes that we read aren't equal to the calculated filesize of
	 *	the source code file, then we shall "throw an exception".
	 */
	if (bytes_read != filesize)
	{
		fprintf(stderr, "error: Failed to read the entire file!" ENDL);

		/*
		 *	Before we exit the program, we must close our access to the source
		 *	code file & de-allocate the newly-allocated memory.
		 */
		free(contents);
		fclose(fileitem);

		exit(EXIT_FAILURE);
	}

	/*
	 *	Let's place that NULL terminator to the end of the newly-allocated
	 *	memory.
	 */
	contents[filesize] = '\0';

	/*
	 *	Now that we finished loading the source code to memory, we will create
	 *	some string storage objects which are to contain the source code that
	 *	was loaded to memory, and the output assembly.
	 *	These string objects are inspired by C++'s string classes, which made
	 *	higher-level string types, allowing for better string manipulation and
	 *	automatic allocation & de-allocation for strings when their sizes
	 *	changed.
	 */

	/* Create the string objects. */
	string_t source, assembly;

	/* Initialize the string objects. */
	string_create(&source);
	string_create(&assembly);

	/*
	 *	Copy the contents of the previously allocated memory to our
	 *	higher-level string object.
	 */
	string_copy(&source, contents);

	/*
	 *	You'll also see here that we created a high-level array type, also
	 *	inspired by C++'s vector classes. Instead of having to manually
	 *	allocate, re-allocate, and/or de-allocate memory to have arrays that
	 *	can change in size, I made higher-level versions of them, which are
	 *	the `vector_t` types that you'll see.
	 */

	/*
	 *	Create the vector object containing the splitted tokens. To clarify
	 *	more, our lexer will read our raw source code, and it'll split it
	 *	into tokens that will be more easy to read by the AST generator.
	 *	These tokens are to be stored in the `tokens` vector.
	 */
	vector_t tokens;

	/* Initialize the `tokens` vector. */
	vector_create(&tokens);

	/*
	 *	Let's now call the lexer, so that it can convert our raw source
	 *	code into seperated tokens, as explained above.
	 */
	int status = lex(&source, &tokens);

	/*
	 *	Let's make sure the lexer didn't encounter any errors before moving on.
	 *	We do this by checking whether or not lexer returned the code 0 or not.
	 *	When code 0 is returned, it means everything went fine.
	 */
	if(status != 0)
	{
		/*
		 *	Since the lexer ran into an error, we must de-initialize the
		 *	strings & vectors that we initialized earlier in the code.
		 */
		string_delete(&source);
		string_delete(&assembly);
		vector_free(&tokens);

		fprintf(stderr, "error: Lexer returned a non-0 value!" ENDL);
		exit(EXIT_FAILURE);
	}

	/*
	 *	Now that we're finished, let's de-initialize the strings & vectors
	 *	that were initialized earlier.
	 */
	string_delete(&source);
	string_delete(&assembly);
	vector_free(&tokens);

	/*
	 *	Let's also de-allocate the memory storing the source code file's
	 *	contents & let's end our access to the source code file.
	 */
	free(contents);
	fclose(fileitem);

	/* We can now gracefully exit! */
	exit(EXIT_SUCCESS);
}