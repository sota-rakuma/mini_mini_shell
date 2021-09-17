#include "minishell.h"

static int	validate_cmd_check(t_cmd *cmd, int *flag, long *cmd_count)
{
	if (ft_strncmp(cmd->str, "<", 2) == 0 || ft_strncmp(cmd->str, "<<", 3) == 0 \
	|| ft_strncmp(cmd->str, ">", 2) == 0 || ft_strncmp(cmd->str, ">>", 3) == 0)
	{
		if (*flag == 0)
			*flag = 1;
		else
			return (1);
	}
	else if (ft_strncmp(cmd->str, "|", 2) == 0)
	{
		if (*flag == 1 || *cmd_count == 0)
			return (1);
		*cmd_count = 0;
	}
	else
	{
		*flag = 0;
		(*cmd_count)++;
	}
	return (0);
}

static int	validate_cmd_check_q(t_cmd *cmd)
{
	size_t	index;

	index = ft_strlen(cmd->str);
	if (!index)
		return (1);
	if (cmd->flag[index - 1] != '1')
	{
		return (1);
	}
	return (0);
}

int	validate_cmd(t_cmd *cmd)
{
	int		flag;
	long	cmd_count;

	flag = 0;
	cmd_count = 0;
	if (ft_strncmp(cmd->str, "|", 2) == 0)
		return (258);
	while (cmd != NULL)
	{
		if (validate_cmd_check(cmd, &flag, &cmd_count) == 1)
			return (258);
		if (validate_cmd_check_q(cmd) == 1)
			return (258);
		cmd = cmd->next;
	}
	if (flag == 1 || cmd_count == 0)
		return (258);
	return (0);
}
