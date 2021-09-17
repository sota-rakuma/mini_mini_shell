#include "minishell.h"

int	check_build_in(t_cmd *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp(cmd->str, "export", 7) || \
	!ft_strncmp(cmd->str, "unset", 6) || \
	!ft_strncmp(cmd->str, "echo", 5) || \
	!ft_strncmp(cmd->str, "exit", 5) || \
	!ft_strncmp(cmd->str, "env", 4) || \
	!ft_strncmp(cmd->str, "pwd", 4) || \
	!ft_strncmp(cmd->str, "cd", 3))
		return (1);
	return (0);
}
