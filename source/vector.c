#include <stdlib.h>

#include "vector.h"

void vector_create(vector_t *vector)
{
	vector->vector_total = vector_total;
	vector->vector_resize = vector_resize;
	vector->vector_add = vector_pushback;
	vector->vector_set = vector_set;
	vector->vector_get = vector_get;
	vector->vector_free = vector_free;
	vector->vector_delete = vector_delete;
	vector->vector_list.capacity = VECTOR_INIT_CAPACITY;
	vector->vector_list.total = 0;
	vector->vector_list.items = malloc(sizeof(void *) * vector->vector_list.capacity);
}

int vector_total(vector_t *vector)
{
	int totalCount = UNDEFINE;
	if(vector)
	{
		totalCount = vector->vector_list.total;
	}
	return totalCount;
}

int vector_resize(vector_t *vector, int capacity)
{
	int status = UNDEFINE;
	if(vector)
	{
		void **items = realloc(vector->vector_list.items, sizeof(void *) * capacity);
		if (items)
		{
			vector->vector_list.items = items;
			vector->vector_list.capacity = capacity;
			status = SUCCESS;
		}
	}
	return status;
}

int vector_pushback(vector_t *vector, void *item)
{
	int status = UNDEFINE;
	if(vector)
	{
		if(vector->vector_list.capacity == vector->vector_list.total)
		{
			status = vector_resize(vector, vector->vector_list.capacity * 2);
			if(status != UNDEFINE)
			{
				vector->vector_list.items[vector->vector_list.total++] = item;
			}
		}
		else
		{
			vector->vector_list.items[vector->vector_list.total++] = item;
			status = SUCCESS;
		}
	}

	return status;
}

int vector_set(vector_t *vector, int index, void *item)
{
	int status = UNDEFINE;
	if(vector)
	{
		if ((index >= 0) && (index < vector->vector_list.total))
		{
			vector->vector_list.items[index] = item;
			status = SUCCESS;
		}
	}
	return status;
}

void *vector_get(vector_t *vector, int index)
{
	void *read_data = NULL;
	if(vector)
	{
		if ((index >= 0) && (index < vector->vector_list.total))
		{
			read_data = vector->vector_list.items[index];
		}
	}

	return read_data;
}

int vector_delete(vector_t *vector, int index)
{
	int status = UNDEFINE;
	int i = 0;
	if(vector)
	{
		if ((index < 0) || (index >= vector->vector_list.total))
			return status;
		vector->vector_list.items[index] = NULL;
		for (i = index; (i < vector->vector_list.total - 1); ++i)
		{
			vector->vector_list.items[i] = vector->vector_list.items[i + 1];
			vector->vector_list.items[i + 1] = NULL;
		}
		vector->vector_list.total--;
		if ((vector->vector_list.total > 0) && ((vector->vector_list.total) == (vector->vector_list.capacity / 4)))
		{
			vector_resize(vector, vector->vector_list.capacity / 2);
		}
		status = SUCCESS;
	}
	return status;
}

int vector_free(vector_t *vector)
{
	int status = UNDEFINE;
	if(vector)
	{
		free(vector->vector_list.items);
		vector->vector_list.items = NULL;
		status = SUCCESS;
	}
	return status;
}