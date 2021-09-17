#include "minishell.h"

static int	inequality_branch_second(t_cmd **cmd, \
int *do_flag)
{
	int	flag;

	flag = 0;
	if (ft_strncmp((*cmd)->str, ">", 2) == 0)
		flag = inequality_r1((*cmd));
	else if (ft_strncmp((*cmd)->str, ">>", 3) == 0)
		flag = inequality_r2((*cmd));
	else if (ft_strncmp((*cmd)->str, "<", 2) == 0)
		flag = inequality_l1((*cmd));
	else if (ft_strncmp((*cmd)->str, "<<", 3) == 0)
		flag = inequality_l2((*cmd));
	else
		return (0);
	delete_list_two(cmd);
	*do_flag = 1;
	return (flag);
}

int	check_redirect(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		do_flag;

	while (*cmd != NULL)
	{
		do_flag = 0;
		if (inequality_branch_second(cmd, &do_flag))
			return (1);
		if (do_flag == 0)
			break ;
	}
	tmp = *cmd;
	while (tmp != NULL)
	{
		do_flag = 0;
		if (inequality_branch_second(&tmp, &do_flag) == 1)
			return (1);
		if (do_flag == 1)
			continue ;
		if (tmp == NULL)
			break ;
		tmp = (tmp)->next;
	}
	return (0);
}
