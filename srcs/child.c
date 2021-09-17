#include "minishell.h"

int	set_fd(int	in_fd, int out_fd)
{
	if (in_fd != 0 && dup2(in_fd, 0) == -1)
	{
		put_error_str("dup2", NULL, 1);
		return (1);
	}
	if (in_fd != 0)
		close (in_fd);
	if (out_fd != 1 && dup2(out_fd, 1) == -1)
	{
		put_error_str("dup2", NULL, 1);
		return (1);
	}
	if (out_fd != 1)
		close (out_fd);
	return (0);
}

char	**make_env_list(t_env *env_list)
{
	int		count;
	char	**res;
	int		index;

	count = ft_bidir_lst_size(env_list);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (res == NULL)
		exit(1);
	index = 0;
	while (index < count)
	{
		if (env_list->var)
			res[index] = ft_strjoin_3(env_list->key, "=", env_list->var);
		else
			res[index] = ft_strdup(env_list->key);
		if (res[index] == NULL)
			exit(1);
		index++;
		env_list = env_list->next;
	}
	res[index] = NULL;
	return (res);
}

/* 子プロセスの始まり */
void	exec_cmd_child(t_cmd *cmd, t_env *env_list_t, \
int in_fd, int out_fd)
{
	char	**cmd_list;
	char	**path_list;
	char	**env_list;
	int		exit_num;

	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(sig_error(g_minishell.exit_num));
	rl_clear_history();
	env_list = make_env_list(env_list_t);
	if (set_fd(in_fd, out_fd) == 1)
		exit(1);
	if (check_redirect(&cmd))
		exit(1);
	translate_string(&cmd, env_list_t);
	if (!cmd)
		exit(0);
	exit_num = search_cmd(&env_list_t, cmd);
	if (exit_num != -1)
		exit (exit_num);
	cmd_list = make_cmd_list(cmd);
	path_list = make_path_list(env_list);
	if (cmd_list == NULL || path_list == NULL)
		exit(1);
	search_path_exec(cmd_list, path_list, env_list);
}
