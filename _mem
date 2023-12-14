#include "shell.h"

/**
 * bfree - frees a pointer and NULLS
 * the address
 *
 * @ptr: address of pointer
 *
 * Return: 1 on success
 *
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
