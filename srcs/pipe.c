#include "minishell.h"

static void	middle_pipe_p(t_common_process *c_p, \
int pipe_fd[2], pid_t id, int where_flag)
{
	if (where_flag != 0)
	{
		close(c_p->in_fd);
	}
	if (where_flag != 2)
	{
		close(pipe_fd[1]);
		c_p->in_fd = pipe_fd[0];
	}
	c_p->id_list[c_p->process_count] = id;
}

static void	middle_pipe_c(t_cmd *pipe_cmd, t_common_process *c_p, \
int pipe_fd[2], int where_flag)
{
	if (where_flag != 2)
		close(pipe_fd[0]);
	free(c_p->id_list);
	if (where_flag == 0)
		exec_cmd_child(pipe_cmd, c_p->env_list, 0, pipe_fd[1]);
	else if (where_flag == 1)
		exec_cmd_child(pipe_cmd, c_p->env_list, c_p->in_fd, pipe_fd[1]);
	else if (where_flag == 2)
		exec_cmd_child(pipe_cmd, c_p->env_list, c_p->in_fd, 1);
}

int	middle_pipe(t_common_process *c_p, int where_flag)
{
	t_cmd	*pipe_cmd;
	pid_t	id;
	int		pipe_fd[2];

	pipe_cmd = make_pipe_cmd(&(c_p->cmd));
	if (pipe_cmd == NULL)
		return (0);
	if (where_flag != 2)
	{
		if (pipe(pipe_fd) == -1)
			return (1);
	}
	id = fork();
	if (id < 0)
		return (1);
	else if (id == 0)
		middle_pipe_c(pipe_cmd, c_p, pipe_fd, where_flag);
	else
		middle_pipe_p(c_p, pipe_fd, id, where_flag);
	free_list_cmd(pipe_cmd);
	return (0);
}
