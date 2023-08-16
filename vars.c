#include "shell.h"
/**
 * is_chain - test if current character in buf is a chain delimeter
 * @info: the parameter of struct
 * @buf: the character buffer
 * @p: The address of current position in buffer
 *
 * Return: 1 if chain delimeter,else return  0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[b] == ';') /* found end of this command */
	{
		buf[b] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - checks that we should continue chaining based on last status
 * @info: The parameter  ofstruct
 * @buf: The character buffer
 * @p: Address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_alias - Replaces the aliases in the tokenized string
 * @info: Parameter of the struct
 *
 * Return: 1 if replaced, 0 if not replaced
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - It Replaces variables in the tokenized string
 * @info: The parameter of the struct
 *
 * Return: 1 if replaced, 0 if not replaced
 */
int replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces the of the string
 * @old: Address of old string
 * @new: string new
 *
 * Return: 1 if replaced, 0 if otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
