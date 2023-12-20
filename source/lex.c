#include <stdio.h>
#include <stdbool.h>
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
		/* Skip whitespace. */
		if(is_whitespace(code->memory[i]))
		{
			i++;
			continue;
		}

		/* Handle keywords. */
		for(int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++)
		{
			if(strncmp(keywords[j], code->memory + i, strlen(keywords[j])) == 0 && (is_whitespace(*(code->memory + i + strlen(keywords[j]))) || *(code->memory + i + strlen(keywords[j])) == '\0') && (i == 0 || is_whitespace(*(code->memory + i - 1))))
			{
				printf("%s\r\n", keywords[j]);
				i += strlen(keywords[j]);
				
				continue;
			}
		}

		/* Handle symbols. Unlike keywords, we do not check for whitespace padding. */
		for(int j = 0; j < sizeof(symbols) / sizeof(symbols[0]); j++)
		{
			if(strncmp(symbols[j], code->memory + i, strlen(symbols[j])) == 0)
			{
				printf("%s\r\n", symbols[j]);
				i += strlen(symbols[j]);
				
				continue;
			}
		}

		/* Handle character literals, not all escape sequences supported here. */
		if(code->memory[i] == '\'')
		{
			int j = i + 1;

			if(code->memory[j] == '\\')
			{
				j++;
				switch(code->memory[j])
				{
				case 'n':
					printf("'\\n'\r\n");
					j++;
					break;
				case 't':
					printf("'\\t'\r\n");
					j++;
					break;
				case 'r':
					printf("'\\r'\r\n");
					j++;
					break;
				case '\'':
				case '\"':
				case '\\':
					printf("'\\%c'\r\n", code->memory[j]);
					j++;
					break;
				default:
					/* Unknown escape sequence! */
					return -1;
				}
			}
			else if(code->memory[j] == '\'')
			{
				/* Empty character literal! */
				return -2;
			}
			else
			{
				printf("'%c'\r\n", code->memory[j]);
				j++;
			}

			if(j < code->size && code->memory[j] == '\'')
			{
				i = j + 1;
				continue;
			}
			else
			{
				/* Unterminated character literal! */
				return -3;
			}
		}

		/* Handle string literals. */
		if (code->memory[i] == '\"')
		{
			int j = i + 1;
			printf("\"");

			while (j < code->size && code->memory[j] != '\"')
			{
				/* Check for escape sequence(s). */
				if (code->memory[j] == '\\')
				{
					j++;
					switch (code->memory[j])
					{
					case 'n':
						printf("\\n");
						break;
					case 't':
						printf("\\t");
						break;
					case 'r':
						printf("\\r");
						break;
					case '\"':
					case '\'':
					case '\\':
						printf("\\%c", code->memory[j]);
						break;
					default:
						/* Invalid escape sequence! */
						return -1;
					}
				}
				else
				{
					/* Handle a regular character. */
					printf("%c", code->memory[j]);
				}

				j++;
			}

			if (j < code->size && code->memory[j] == '\"')
			{
				printf("\"\r\n");
				i = j + 1;
				continue;
			}
			else
			{
				/* Unterminated string literal! */
				return -2;
			}
		}

		/* Handle identifiers. */
		if(is_alphabet(code->memory[i]) || code->memory[i] == '_')
		{
			int j = i + 1;
			while(j < code->size && is_valid_identifier_char(code->memory[j]))
			{
				j++;
			}

			printf("%.*s\r\n", j - i, code->memory + i);

			i = j;
			continue;
		}

		if(i < code->size)
		{
			i++;
		}
	}

	return 0;
}