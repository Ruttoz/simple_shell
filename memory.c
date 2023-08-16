#include "shell.h"

/**
 * bfree - Itfrees a pointer, NULLs the address
 * @ptr: Address of  pointer to free
 *
 * Return: 1 if freed, and if not freed 0.
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
