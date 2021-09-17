#include "minishell.h"

int	count_pipe(t_cmd *cmd)
{
	int	res;

	res = 0;
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->str, "|", 2) == 0)
			res++;
		cmd = cmd->next;
	}
	return (res);
}

t_cmd	*make_pipe_cmd(t_cmd **cmd)
{
	t_cmd	*res;
	t_cmd	*tmp;
	t_cmd	*tmp_pre;

	res = *cmd;
	tmp = *cmd;
	res->prev = NULL;
	while (tmp != NULL && ft_strncmp(tmp->str, "|", 2) != 0)
	{
		tmp_pre = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		*cmd = NULL;
		return (res);
	}
	tmp_pre->next = NULL;
	*cmd = (tmp->next);
	free_list_cmd_one(tmp);
	return (res);
}

void	delete_list_two_next(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = (cmd->next);
	if (tmp == NULL)
		return ;
	cmd->next = ((cmd->next)->next);
	tmp = cmd->next;
	if (tmp == NULL)
		return ;
	cmd->next = ((cmd->next)->next);
}

/* void	delete_list_two(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	*cmd = (*cmd)->next;
	*cmd = (*cmd)->next;
	if (*cmd == NULL)
		free_list_cmd(tmp);
} */
void	delete_list_two(t_cmd **cmd)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	tmp1 = (*cmd);
	if (tmp1)
		tmp2 = tmp1->next;
	if ((*cmd)->prev == NULL)
	{
		(*cmd) = ((*cmd)->next)->next;
		if (*cmd != NULL)
			(*cmd)->prev = NULL;
		free_list_cmd_one(tmp1);
		free_list_cmd_one(tmp2);
		return ;
	}
	if (((*cmd)->next)->next != NULL)
		((*cmd)->next)->next->prev = (*cmd)->prev;
	((*cmd)->prev)->next = ((*cmd)->next)->next;
	*cmd = ((*cmd)->next)->next;
	free_list_cmd_one(tmp1);
	free_list_cmd_one(tmp2);
}
