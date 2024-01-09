#include <stdlib.h>

#include "vector.h"

/**
 *	@brief Initialize a vector object.
 *	@param vector The pointer to the vector object.
 */
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

/**
 *	@brief Get the total amount of items in a vector object.
 *	@param vector The pointer to the vector object.
 *	@return The total count of items in the vector object.
 */
int vector_total(vector_t *vector)
{
	int total_count = UNDEFINE;
	if(vector)
	{
		total_count = vector->vector_list.total;
	}
	return total_count;
}

/**
 *	@brief Change the size of a vector object.
 *	@param vector The pointer to the vector object.
 *	@param capacity The size that we should re-size the vector object to.
 *	@return The status code from re-sizing the vector object.
 */
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

/**
 *	@brief Add a pointer of an object to the vector object.
 *	@param vector The pointer to the vector object.
 *	@param item The pointer to the object that should be added to the vector
 *				object.
 *	@return The status code from adding the object to the vector object.
 */
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

/**
 *	@brief Delete an entry from a vector object.
 *	@param vector The vector object to target.
 *	@param index The index of the vector object in which we want to delete the
 *				 entry.
 *	@return The status code from deleting the entry from the vector object.
*/
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

/**
 *	@brief De-initialize a vector object.
 *	@param vector The pointer to the vector object.
 *	@return The status code from de-initializing the vector object.
 */
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