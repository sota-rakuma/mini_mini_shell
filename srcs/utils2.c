#include "minishell.h"

void	put_error_str(char *cmd, char *message, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (flag == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(message, 2);
	}
	else if (flag == 1)
	{
		perror(cmd);
	}
}

void	re_chain_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		cmd->m_next = cmd ->next;
		cmd = cmd->next;
	}
}

void	free_list_cmd_one(t_cmd *cmd)
{
	free(cmd->str);
	free(cmd->flag);
	free(cmd->tmp_name);
	free(cmd);
}

void	ft_exit(int	exit_num)
{
	close_tmpfile();
	exit(exit_num);
}

void	ft_free_all_bidir_lst(t_bilst *env_lst)
{
	t_bilst	*tmp;

	if (env_lst->prev)
	{
		while (env_lst)
		{
			tmp = env_lst->prev;
			ft_free_pointer(env_lst->key, env_lst->var, NULL, NULL);
			free(env_lst);
			env_lst = tmp;
		}
	}
	else
	{
		while (env_lst)
		{
			tmp = env_lst->next;
			ft_free_pointer(env_lst->key, env_lst->var, NULL, NULL);
			free(env_lst);
			env_lst = tmp;
		}
	}
}
