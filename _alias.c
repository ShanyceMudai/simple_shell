#include "shell.h"

/**
 * myHistory - displays the history list
 *
 * @info: structure containing potential arguments
 *
 * Return: 0 on success
 *
 */
int myHistory(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 *
 * @info: parameter struct
 *
 * @str: string
 *
 * Return: 0 on success
 *
 */
int unsetAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		getIndexnode(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - sets alias of string
 *
 * @info: parameter struct
 *
 * @str: string
 *
 * Return: 0 on success
 *
 */
int setAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - prints an alias
 *
 * @node: alias node
 *
 * Return: 0 on success
 *
 */
int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the builtin alias
 *
 * @info: structure containing potential arguments
 *
 * Return: 0 on success
 *
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
