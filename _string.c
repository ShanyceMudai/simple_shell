#include "shell.h"

/**
 * _strlen - returns length of a string
 *
 * @s: string
 *
 * Return: length of string(s)
 *
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares 2 strings
 *
 * @s1: string one
 *
 * @s2: string two
 *
 * Return: 0 if the strings are equal
 *
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * startString - checks if needle starts with haystack
 *
 * @haystack: string to search
 *
 * @needle: substring to find
 *
 * Return: address of next char of haystack
 *
 */
char *startString(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates 2 strings
 *
 * @dest: destination buffer
 *
 * @src: source buffer
 *
 * Return: pointer to dest buffer
 *
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
