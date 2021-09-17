#include "minishell.h"
#include <fcntl.h>
#include <string.h>

t_minishell	g_minishell;

int	rl_loop_get_cmd(t_cmd **cmd)
{
	char	*line;

	line = readline("minishell > ");
	if (line == NULL)
	{
		ft_putendl_fd("\033[1Aminishell > exit", 2);
		ft_exit(g_minishell.exit_num);
	}
	else if (ft_strlen(line) > 0)
		add_history(line);
	*cmd = parse_cmd(&line);
	if (str_is_space_only(line, 0))
	{
		free(line);
		return (1);
	}
	free(line);
	if (*cmd == NULL && *line != '\0')
	{
		ft_exit(EXIT_FAILURE);
	}
	return (0);
}

void	rl_loop(t_env *env_list)
{
	t_cmd	*cmd;
	int		flag;

	while (1)
	{
		if (rl_loop_get_cmd(&cmd))
			continue ;
		flag = validate_cmd(cmd);
		if (flag != 0)
		{
			free_list_cmd(cmd);
			g_minishell.exit_num = flag;
			ft_putendl_fd("syntax error", 2);
		}
		else
			g_minishell.exit_num = exec_cmd(cmd, &env_list);
	}
	ft_free_all_bidir_lst(env_list);
}

int	main(int ac, char **argv, char **envp)
{
	t_env	*env_list;

	if (ac == 0 && argv == NULL && envp == NULL)
		return (1);
	g_minishell.exit_num = 0;
	g_minishell.tmp_file = NULL;
	if (signal(SIGINT, shell_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (sig_error(g_minishell.exit_num));
	env_list = ft_init_env(envp);
	if (env_list == NULL)
		return (1);
	rl_loop(env_list);
	rl_clear_history();
	return (0);
}
