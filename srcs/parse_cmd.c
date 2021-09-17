#include "minishell.h"

static int	line_count(char *str)
{
	size_t		index;
	int			flag;
	long		list_count;

	flag = 0;
	list_count = 1;
	index = 0;
	while (str[index] != '\0')
	{
		if ((ft_isspace(str[index]) && !ft_isspace(str[index + 1]) && \
		str[index + 1] != '\0' && flag == 0) || str[index] == '|' || \
		str[index] == '<')
			list_count++;
		else if (str[index] == '\'' || str[index] == '\"')
			flag = ~flag;
		index++;
	}
	if (ft_isspace(str[0]))
		list_count--;
	if (flag == 1)
		return (-1);
	return (list_count);
}

t_cmd	*parse_cmd(char **str)
{
	t_cmd	*cmd;
	long	list_num;

	list_num = line_count(*str);
	if (list_num == -1)
		return (NULL);
	else if (list_num > INT_MAX)
	{
		free(*str);
		*str = ft_strdup(" ");
		if (*str == NULL)
			ft_exit(1);
		ft_putendl_fd("bash: Argument list too long", 2);
		return (NULL);
	}
	cmd = NULL;
	set_parse_cmd(&cmd, *str);
	return (cmd);
}
