#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "string.h"
#include "vector.h"
#include "lex.h"
#include "endl.h"

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
				token_t *token = malloc(sizeof(token_t));
				token->type = TYPE_KEYWORD;
				string_create(&token->value.keyword);
				string_copy(&token->value.keyword, (char *)&keywords[j]);
				vector_pushback(tokens, token);

				printf("%s" ENDL, keywords[j]);
				i += strlen(keywords[j]);
				
				continue;
			}
		}

		/* Handle symbols. Unlike keywords, we do not check for whitespace padding. */
		for(int j = 0; j < sizeof(symbols) / sizeof(symbols[0]); j++)
		{
			if(strncmp(symbols[j], code->memory + i, strlen(symbols[j])) == 0)
			{
				token_t *token = malloc(sizeof(token_t));
				token->type = TYPE_SYMBOL;
				string_create(&token->value.symbol);
				string_copy(&token->value.symbol, (char *)&keywords[j]);
				vector_pushback(tokens, token);

				printf("%s" ENDL, symbols[j]);
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
					printf("'\\n'" ENDL);
					j++;
					break;
				case 't':
					printf("'\\t'" ENDL);
					j++;
					break;
				case 'r':
					printf("'\\r'" ENDL);
					j++;
					break;
				case '\'':
				case '\"':
				case '\\':
					token_t *token = malloc(sizeof(token_t));
					token->type = TYPE_CHAR;
					token->value.charlit = code->memory[j];
					vector_pushback(tokens, token);

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
				token_t *token = malloc(sizeof(token_t));
				token->type = TYPE_CHAR;
				token->value.charlit = code->memory[j];
				vector_pushback(tokens, token);

				printf("'%c'" ENDL, code->memory[j]);
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
		if(code->memory[i] == '\"')
		{
			int j = i + 1;

			token_t *token = malloc(sizeof(token_t));
			token->type = TYPE_STRING;
			string_create(&token->value.stringlit);

			printf("\"");

			while(j < code->size && code->memory[j] != '\"')
			{
				/* Check for escape sequence(s). */
				if(code->memory[j] == '\\')
				{
					j++;
					switch(code->memory[j])
					{
					case 'n':
					case 't':
					case 'r':
					case '\"':
					case '\'':
					case '\\':
						printf("\\%c", code->memory[j]);
						string_concatenate_character(&token->value.stringlit, code->memory[j]);
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
					string_concatenate_character(&token->value.stringlit, code->memory[j]);
				}

				j++;
			}

			if (j < code->size && code->memory[j] == '\"')
			{
				printf("\"" ENDL);
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
			token_t *token = malloc(sizeof(token_t));
			token->type = TYPE_IDENTIFIER;
			string_create(&token->value.identifier);

			int j = i + 1;
			while(j < code->size && is_valid_identifier_char(code->memory[j]))
			{
				j++;
			}

			/* Might edit this later so that we don't need to use `sprintf`. */
			char buffer[128];
			sprintf(buffer, "%.*s", j - i, code->memory + i);

			string_copy(&token->value.identifier, buffer);

			printf("%s" ENDL, token->value.identifier.memory);

			i = j;
			continue;
		}

		/* We still haven't finished handling numbers! This will be implemented very soon. */
		if(is_digit(code->memory[i]) || (code->memory[i] == '.' && is_digit(code->memory[i + 1])))
		{
			int j = i;
			bool is_float = false;

			while (is_digit(code->memory[j]) || code->memory[j] == '.')
			{
				if(code->memory[j] == '.')
				{
					is_float = true;
				}

				j++;
			}

			if (is_float && code->memory[j] == 'f')
			{
				j++;
			}

			token_t *token = malloc(sizeof(token_t));
			token->type = is_float ? TYPE_FLOAT : (is_valid_identifier_char(code->memory[i]) ? TYPE_IDENTIFIER : TYPE_INTEGER);

			if(is_float == true)
				string_create(&token->value.floatlit);
			else if(is_float == false)
				string_create(&token->value.integerlit);

			char buffer[128];
			strncpy(buffer, code->memory + i, j - i);
			buffer[j - i] = '\0';

			if(is_float == true)
				string_copy(&token->value.floatlit, buffer);
			else if(is_float == false)
				string_copy(&token->value.integerlit, buffer);

			vector_pushback(tokens, token);

			if(is_float == true)
				printf("%s" ENDL, token->value.floatlit.memory);
			else if(is_float == false)
				printf("%s" ENDL, token->value.integerlit.memory);

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