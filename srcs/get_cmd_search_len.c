#include "minishell.h"

static size_t	search_len_1(size_t *str_index, size_t len)
{
	(*str_index)++;
	return (len);
}

static size_t	search_len_2(size_t *str_index, size_t len)
{
	if (len == 0)
	{
		(*str_index)++;
		len++;
		return (len);
	}
	else if (len != 0)
		return (len);
	return (len);
}

static size_t	search_len_3(char *str, size_t *str_index, size_t len)
{
	if (len == 0)
	{
		(*str_index)++;
		len++;
		if (str[*str_index] == '<')
		{
			(*str_index)++;
			len++;
		}
		return (len);
	}
	else if (len != 0)
		return (len);
	return (len);
}

static size_t	search_len_4(char *str, size_t *str_index, size_t len)
{
	if (len == 0)
	{
		(*str_index)++;
		len++;
		if (str[*str_index] == '>')
		{
			(*str_index)++;
			len++;
		}
		return (len);
	}
	else if (len != 0)
		return (len);
	return (len);
}

size_t	get_cmd_search_len(char *str, size_t *str_index)
{
	int		flag;
	size_t	len;

	len = 0;
	flag = 0;
	while (str[*str_index] != '\0')
	{
		if ((ft_isspace(str[*str_index]) && flag == 0))
			return (search_len_1(str_index, len));
		else if ((str[*str_index] == '|') && flag == 0)
			return (search_len_2(str_index, len));
		else if ((str[*str_index] == '<') && flag == 0)
			return (search_len_3(str, str_index, len));
		else if ((str[*str_index] == '>') && flag == 0)
			return (search_len_4(str, str_index, len));
		else if (str[*str_index] == '\'' || str[*str_index] == '\"')
			change_flag_quart(str, str_index, &flag);
		len++;
		(*str_index)++;
	}
	return (len);
}
