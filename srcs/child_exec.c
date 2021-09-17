#include "minishell.h"

static int	exec_cmd_is_cmd(char *tmp_cmd, char **cmd_list, \
char **env_list, struct stat stat_stack)
{
	if (execve(tmp_cmd, cmd_list, env_list) == -1)
	{
		if (S_ISDIR(stat_stack.st_mode))
		{
			return (126);
		}
		else
		{
			return (125);
		}
	}
	return (1);
}

static int	try_exec(char **cmd_list, char **path_list, char **env_list)
{
	char		*tmp_cmd;
	int			index;
	struct stat	stat_stack;
	int			error_num;

	index = 0;
	error_num = 0;
	while (path_list[index] != NULL)
	{
		tmp_cmd = ft_strjoin_3(path_list[index], "/", cmd_list[0]);
		if (tmp_cmd == NULL)
		{
			exit(1);
		}
		if (stat(tmp_cmd, &stat_stack) == 0)
			error_num = exec_cmd_is_cmd(tmp_cmd, cmd_list, \
			env_list, stat_stack);
		free(tmp_cmd);
		index++;
	}
	return (error_num);
}

void	put_error_message(char **cmd_list, char **path_list, \
char **env_list, int error_num)
{
	if (error_num == 0)
	{
		put_error_str(cmd_list[0], "command not found", 0);
		double_char_free_4(cmd_list, path_list, env_list, NULL);
		exit(127);
	}
	else if (error_num == 126)
	{
		put_error_str(cmd_list[0], "Is a directory", 0);
		double_char_free_4(cmd_list, path_list, env_list, NULL);
		exit(126);
	}
	else if (error_num == 127 || error_num == 125)
	{
		put_error_str(cmd_list[0], "Permission denied", 0);
		double_char_free_4(cmd_list, path_list, env_list, NULL);
		exit(126);
	}
	else
	{
		put_error_str(cmd_list[0], "command not found", 0);
		double_char_free_4(cmd_list, path_list, env_list, NULL);
		exit(1);
	}
}

char	*search_path_exec(char **cmd_list, char **path_list, char **env_list)
{
	int			error_num;
	struct stat	stat_stack;

	error_num = 0;
	if (cmd_list[0][0] == '.' || cmd_list[0][0] == '/' || \
	cmd_list[0][0] == '\0')
	{
		if (stat(cmd_list[0], &stat_stack) == 0)
		{
			error_num = exec_cmd_is_cmd(cmd_list[0], cmd_list, \
			env_list, stat_stack);
		}
	}
	else
		error_num = try_exec(cmd_list, path_list, env_list);
	put_error_message(cmd_list, path_list, env_list, error_num);
	exit(error_num);
}
