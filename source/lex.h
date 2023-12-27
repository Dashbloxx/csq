#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "string.h"
#include "vector.h"

static inline bool is_whitespace(char character)
{
	return character == ' ' || character == '\t' || character == '\f' || character == '\v' || character == '\n' || character == '\r';
}

static inline bool is_alphabet(char character)
{
	return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

static inline bool is_alphanumeric(char character)
{
	return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9');
}

static inline bool is_digit(char character)
{
	return character >= '0' && character <= '9';
}

static inline bool is_valid_identifier_char(char character)
{
	return is_alphanumeric(character) || character == '_';
}

typedef struct
{
	string_t value_string;
	string_t value_identifier;
	string_t value_keyword;
	string_t value_symbol;
	char value_char;
	ssize_t value_signed;
	size_t value_unsigned;
} token_t;

int lex(string_t *code, vector_t *tokens);