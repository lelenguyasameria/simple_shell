#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/**
 **_memset - occupiesthe  memory with a constant byte
 *@s:  pointer to memory
 *@b: the byte to occupy constant byte with
 *@n: number of byts to be occupied
 *Return: pointer to the memory
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string made up of other strings
 * @pp: string made up of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates memory
 * @ptr: pointer to the before allocated memory
 * @old_size: size of previous alocated memory block
 * @new_size: size of new block
 *
 * Return: pointer to old bloc
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
