#include <stdlib.h>
#include <string.h>

#include "string.h"
#include "vector.h"

/**
 *	@brief Initialize a string object.
 *	@param string A pointer to the string object.
 *	@return Returns a status code. Will always return 0 in this case.
 */
int string_create(string_t *string)
{
	string->memory = NULL;
	string->size = 0;
	string->allocated = false;

	return 0;
}

/**
 *	@brief Copy a null-terminated buffer to a string object.
 *	@param string The string object to have the data copied to.
 *	@param buffer The null-terminated buffer that should be copied to the string object.
 *	@return Returns a status code. Will always return 0 in this case.
 */
int string_copy(string_t *string, char *buffer)
{
	size_t buffer_size;

	if(buffer == NULL)
	{
		buffer_size = 0;
		return 0;
	}
	else
	{
		buffer_size = strlen(buffer);
	}

	if(string->allocated == false)
	{
		string->memory = malloc(buffer_size + 1);
		string->allocated = true;
	}
	else
	{
		string->memory = realloc(string->memory, string->size + buffer_size + 1);
		string->allocated = true;
	}
	
	strcpy(string->memory, buffer);
	string->memory[buffer_size] = '\0';
	string->size += buffer_size;

	return 0;
}

/**
 *	@brief Concatenate a null-terminated buffer to a string object.
 *	@param string The string object to concatenate to.
 *	@param buffer The null-terminated buffer that should be concatenated to the string object.
 *	@return Returns a status code. Will always return 0 in this case.
 */
int string_concatenate(string_t *string, char *buffer)
{
	size_t buffer_size;

	if(buffer == NULL)
	{
		buffer_size = 0;
		return 0;
	}
	else
	{
		buffer_size = strlen(buffer);
	}

	if(string->allocated == false)
	{
		string->memory = malloc(buffer_size + 1);
		string->allocated = true;
	}
	else
	{
		string->memory = realloc(string->memory, string->size + buffer_size + 1);
		string->allocated = true;
	}
	
	strcat(string->memory, buffer);
	string->size += buffer_size;

	return 0;
}

/**
 *	@brief Obtains a smaller string from a larger string, using a specified range.
 *	@param a The first value in the range.
 *	@param b The second value in the range.
 *	@param input The large string.
 *	@param output The output string, which will store the extracted string.
 *	@return Returns a status code.
 */
int string_substring(size_t a, size_t b, string_t *input, string_t *output)
{
	if (input == NULL || output == NULL || input->memory == NULL)
	{
		return -1;
	}

	if (b < a || b >= input->size)
	{
		return -2;
	}

	size_t substring_length = b - a + 1;

	if(output->allocated == false)
	{
		output->memory = malloc(substring_length + 1);
		output->allocated = true;
	}
	else
	{
		output->memory = realloc(output->memory, substring_length + 1);
		output->allocated = true;
	}

	strncpy(output->memory, input->memory + a, substring_length);

	output->memory[substring_length] = '\0';

	output->size = substring_length;

	return 0;
}

/**
 *	@brief Find a substring's position from a larger string.
 *	@param string The large string from where we should search for the substring.
 *	@param substring The buffer we're looking for.
 *	@param index The index that contains the position in where the first occurence of the substring is found.
 *	@return Returns a status value.
 */
int string_find(string_t *string, char *substring, size_t *index)
{
	if(string == NULL || substring == NULL || string->memory == NULL)
	{
		return -1;
	}

	char *position = strstr(string->memory, substring);

	if(position != NULL)
	{
		*index = position - string->memory;
		return 0;
	}
	else
	{
		return -2;
	}

	return -3;
}

/**
 *	@brief Split a string by a delimiter.
 *	@param input The string object to split.
 *	@param delimiter The null-terminated string that contains the data that the string object should be cut by.
 *	@param output_vector The vector containing the split up string.
 *	@return Returns a status code.
 */
int string_split(string_t *input, char *delimiter, vector_t *output_vector)
{
	if(input == NULL || input->memory == NULL || input->size == 0)
	{
		return -1;
	}

	string_t temporary_string;
	string_create(&temporary_string);

	for(size_t i = 0; i < input->size; ++i)
	{
		if(strncmp(&input->memory[i], delimiter, strlen(delimiter)) == 0)
		{
			vector_pushback(output_vector, temporary_string.memory);
			string_create(&temporary_string);
			i += strlen(delimiter) - 1;
		}
		else
		{
			string_concatenate(&temporary_string, &input->memory[i]);
		}
	}

	vector_pushback(output_vector, temporary_string.memory);

	string_delete(&temporary_string);

	return 0;
}


/**
 * @brief Concatenate a character to a string object.
 * @param string The string object to concatenate to.
 * @param character The character to be concatenated.
 * @return Returns a status code. Will always return 0 in this case.
 */
int string_concatenate_character(string_t *string, char character)
{
	if (string->allocated == false)
	{
		string->memory = malloc(2);
		string->allocated = true;
	}
	else
	{
		string->memory = realloc(string->memory, string->size + 2);
		string->allocated = true;
	}

	string->memory[string->size] = character;
	string->memory[string->size + 1] = '\0';
	string->size += 1;

	return 0;
}

/**
 * @brief Copy a specified number of characters from a buffer to a string object.
 * @param string The string object to have the data copied to.
 * @param buffer The buffer that should be copied to the string object.
 * @param count The number of characters to copy.
 * @return Returns a status code. Will always return 0 in this case.
 */
int string_copy_n(string_t *string, const char *buffer, size_t count)
{
	if (buffer == NULL || count == 0)
	{
		return 0;
	}

	if (string->allocated == false)
	{
		string->memory = malloc(count + 1);
		string->allocated = true;
	}
	else
	{
		string->memory = realloc(string->memory, string->size + count + 1);
	}

	strncpy(string->memory + string->size, buffer, count);
	string->memory[string->size + count] = '\0';
	string->size += count;

	return 0;
}

/**
 *	@brief de-initialize a string object.
 *	@param string A pointer to the string object.
 *	@return The status code, will always return 0.
 */
int string_delete(string_t *string)
{
	if(string->allocated == true)
	{
		free(string->memory);
		string->allocated = false;
		string->memory = NULL;
	}

	string->size = 0;

	return 0;
}