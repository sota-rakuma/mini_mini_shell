#include "minishell.h"

int	inequality_r1(t_cmd *cmd)
{
	int	out_fd;

	cmd = cmd->next;
	if (cmd == NULL)
		return (1);
	out_fd = open(cmd->str, O_WRONLY | O_CREAT | O_TRUNC, \
	S_IREAD | S_IWRITE);
	if (out_fd == -1)
	{
		put_error_str(cmd->str, NULL, 1);
		return (1);
	}
	if (dup2(out_fd, 1) == -1)
	{
		put_error_str("dup2", NULL, 1);
		close(out_fd);
		return (1);
	}
	close(out_fd);
	return (0);
}

int	inequality_r2(t_cmd *cmd)
{
	int	out_fd;

	cmd = cmd->next;
	if (cmd == NULL)
		return (1);
	out_fd = open(cmd->str, O_WRONLY | O_CREAT | O_APPEND, \
	S_IREAD | S_IWRITE);
	if (out_fd == -1)
	{
		put_error_str(cmd->str, NULL, 1);
		return (1);
	}
	if (dup2(out_fd, 1) == -1)
	{
		put_error_str("dup2", NULL, 1);
		close(out_fd);
		return (1);
	}
	close(out_fd);
	return (0);
}

int	inequality_l1(t_cmd *cmd)
{
	int	in_fd;

	cmd = cmd->next;
	if (cmd == NULL)
		return (1);
	in_fd = open(cmd->str, O_RDONLY);
	if (in_fd == -1)
	{
		put_error_str(cmd->str, NULL, 1);
		return (1);
	}
	if (dup2(in_fd, 0) == -1)
	{
		put_error_str("dup2", NULL, 1);
		close(in_fd);
		return (1);
	}
	close(in_fd);
	return (0);
}

int	inequality_l2(t_cmd *cmd)
{
	int	in_fd;

	in_fd = open(cmd->tmp_name, O_RDONLY);
	if (dup2(in_fd, 0) == -1)
	{
		put_error_str("dup2", NULL, 1);
		close(in_fd);
		return (1);
	}
	close(in_fd);
	return (0);
}
