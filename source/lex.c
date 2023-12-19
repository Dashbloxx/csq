#include <stdio.h>
#include <string.h>

#include "string.h"
#include "vector.h"
#include "lex.h"

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const char *symbols[] = {
    "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
    "&", "|", "^", "~", "<<", ">>", "(", ")", "{", "}", "[", "]", ";", ",", "."
};

enum
{
    AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO,
    DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO, IF,
    INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC,
    STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE
};

enum
{
    ADD, SUB, MUL, DIV, ASSIGN, EQUAL, NOT_EQUAL, LESS_THAN, GREATER_THAN, LESS_EQUAL, GREATER_EQUAL,
    LOGICAL_AND, LOGICAL_OR, LOGICAL_NOT, BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT,
    LEFT_SHIFT, RIGHT_SHIFT, OPEN_PAREN, CLOSE_PAREN, OPEN_BRACE, CLOSE_BRACE, OPEN_BRACKET,
    CLOSE_BRACKET, SEMICOLON, COMMA, PERIOD
};

int lex(string_t *code, vector_t *tokens)
{
	int i = 0;

	while(i < code->size)
	{
		if(is_whitespace(code->memory[i]))
		{
			i++;
			continue;
		}

		for(int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++)
		{
			if(strncmp(keywords[j], code->memory + i, strlen(keywords[j])) == 0 && (is_whitespace(*(code->memory + i + strlen(keywords[j]))) || *(code->memory + i + strlen(keywords[j])) == '\0') && (i == 0 || is_whitespace(*(code->memory + i - 1))))
			{
				printf("%s\r\n", keywords[j]);
				i += strlen(keywords[j]);
				
				break;
			}
		}

		if(i < code->size)
		{
			i++;
		}
	}

	return 0;
}