#include "minishell.h"

void	make_id_list(t_common_process *common_process, int pipe_count)
{
	pid_t	*id_list;

	id_list = (pid_t *)malloc(sizeof(pid_t) * (pipe_count + 1));
	common_process->id_list = id_list;
	if (id_list == NULL)
	{
		ft_exit(1);
	}
	ft_bzero(id_list, sizeof(pid_t) * (pipe_count + 1));
}

static void	init_common_process(t_common_process *common_process, \
t_cmd *cmd, t_env *env_list)
{
	common_process->cmd = cmd;
	common_process->env_list = env_list;
	common_process->process_count = 0;
	common_process->id_list = NULL;
	common_process->in_fd = 0;
	common_process->out_fd = 1;
}

int	exec_cmd(t_cmd *cmd, t_env **env_list)
{
	int					pipe_count;
	t_common_process	common_process;
	int					flag;

	init_common_process(&common_process, cmd, *env_list);
	flag = set_tmpfile(cmd, &common_process);
	if (flag)
	{
		free_list_cmd(common_process.cmd);
		if (flag == -1 || g_minishell.exit_num > 128)
			return (1);
		return (print_error_return("minishell: tmpfile can't open"));
	}
	pipe_count = count_pipe(cmd);
	if (pipe_count == 0)
	{
		flag = exec_cmd_no_pipe(&common_process);
		free_list_cmd(common_process.cmd);
	}
	else
		flag = exec_cmd_pipe(&common_process, pipe_count);
	close_tmpfile();
	*env_list = common_process.env_list;
	return (flag);
}
