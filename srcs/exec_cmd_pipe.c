#include "minishell.h"

static int	wait_child_process(t_common_process *common_process)
{
	int	process_count;
	int	flag;

	process_count = 0;
	flag = 0;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (sig_error(g_minishell.exit_num));
	while (process_count != common_process->process_count - 1)
	{
		if (common_process->id_list[process_count] == 0)
			return (flag);
		waitpid(common_process->id_list[process_count], &flag, 0);
		process_count++;
	}
	if (common_process->id_list[process_count] == 0)
		return (flag);
	waitpid(common_process->id_list[process_count], &flag, 0);
	if (WIFSIGNALED(flag))
		return (proc_child_stop_by_sig(WTERMSIG(flag)));
	return (WEXITSTATUS(flag));
}

int	restore_stdio(int save_fd[2], int return_value)
{
	if (dup2(save_fd[0], 0) == -1 || dup2(save_fd[1], 1) == -1)
		return (1);
	close(save_fd[0]);
	close(save_fd[1]);
	return (return_value);
}

int	exec_cmd_no_pipe_set_fd(t_common_process *common_process, int save_fd[2])
{
	int	flag;

	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
	if (save_fd[0] == -1 || save_fd[1] == -1)
		return (1);
	if (check_redirect(&common_process->cmd) == 1)
		return (restore_stdio(save_fd, 1));
	if ((common_process->cmd) == NULL)
		return (restore_stdio(save_fd, 0));
	if (check_build_in(common_process->cmd))
		translate_string(&common_process->cmd, common_process->env_list);
	flag = search_cmd(&common_process->env_list, common_process->cmd);
	if (flag != -1)
		return (restore_stdio(save_fd, flag));
	return (-1);
}

int	exec_cmd_no_pipe(t_common_process *common_process)
{
	int		flag;
	pid_t	id;
	int		save_fd[2];

	flag = exec_cmd_no_pipe_set_fd(common_process, save_fd);
	if (flag != -1)
		return (flag);
	id = fork();
	if (id < 0)
		restore_stdio(save_fd, 1);
	else if (id == 0)
		exec_cmd_child(common_process->cmd, common_process->env_list, 0, 1);
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			return (sig_error(1));
		waitpid(id, &flag, 0);
		if (restore_stdio(save_fd, 0) == 1)
			return (1);
		if (signal(SIGINT, shell_sig_handler) == SIG_ERR)
			return (sig_error(1));
		if (WIFSIGNALED(flag))
			return (proc_child_stop_by_sig(WTERMSIG(flag)));
	}
	return (WEXITSTATUS(flag));
}

int	exec_cmd_pipe(t_common_process *common_process, int pipe_count)
{
	int		flag;

	make_id_list(common_process, pipe_count);
	flag = 0;
	while (common_process->process_count <= pipe_count && flag == 0)
	{
		if (common_process->process_count == 0)
			flag = middle_pipe(common_process, 0);
		else if (common_process->process_count < pipe_count)
			flag = middle_pipe(common_process, 1);
		else if (common_process->process_count == pipe_count)
			flag = middle_pipe(common_process, 2);
		(common_process->process_count)++;
	}
	if (flag != 0)
	{
		free_list_cmd(common_process->cmd);
		print_error_return("minishell: fail make child process");
	}
	flag = wait_child_process(common_process);
	free(common_process->id_list);
	if (signal(SIGINT, shell_sig_handler) == SIG_ERR)
		return (sig_error(g_minishell.exit_num));
	return (flag);
}
