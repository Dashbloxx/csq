#include "string.h"
#include "vector.h"
#include "ast.h"
#include "lex.h"

int ast(vector_t *tokens, vector_t *objects)
{
	for(int i = 0; i < vector_total(tokens); i++)
	{
		int j = 0;
		token_t *token0 = vector_get(tokens, i);
		switch(token0->type)
		{
			
		}
	}

	return 0;
}