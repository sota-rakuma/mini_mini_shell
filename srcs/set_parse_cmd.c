#include "minishell.h"

int	str_is_space_only(char *str, size_t str_index)
{
	while (str[str_index] != '\0' && ft_isspace(str[str_index]))
		(str_index)++;
	if (str[str_index] == '\0')
		return (1);
	return (0);
}

void	add_cmd(t_cmd **res, t_cmd *new)
{
	t_cmd	*tmp;

	new->top = *res;
	if (*res == NULL)
	{
		new->top = new;
		*res = new;
		return ;
	}
	tmp = *res;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	tmp->m_next = new;
}

void	free_list_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		free(cmd->str);
		free(cmd->flag);
		free(cmd->tmp_name);
		free(cmd);
		cmd = tmp;
	}
}

static t_cmd	*get_cmd_start_len(char *str, size_t *str_index)
{
	size_t	start;
	size_t	len;

	while (str[*str_index] != '\0' && ft_isspace(str[*str_index]))
		(*str_index)++;
	start = *str_index;
	len = get_cmd_search_len(str, str_index);
	return (ft_substr_cmd(str, start, len));
}

int	set_parse_cmd(t_cmd **res, char *str)
{
	size_t		str_index;
	t_cmd		*new_one;

	str_index = 0;
	while (str[str_index] != '\0')
	{
		if (str_is_space_only(str, str_index) == 1)
			break ;
		new_one = get_cmd_start_len(str, &str_index);
		if (new_one == NULL)
		{
			free_list_cmd(*res);
			return (1);
		}
		add_cmd(res, new_one);
	}
	return (0);
}
