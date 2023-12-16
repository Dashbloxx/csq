#pragma once

#include <stdbool.h>

static inline bool is_whitespace(char character)
{
	return character == ' ' || character == '\t' || character == '\f' || character == '\v';
}

static inline bool is_alphabet(char character)
{
	return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}