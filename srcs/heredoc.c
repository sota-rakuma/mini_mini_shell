/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:25:25 by takataok          #+#    #+#             */
/*   Updated: 2021/09/02 21:50:02 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_keyword_flag(char *flag)
{
	while (*flag == '1')
		flag++;
	if (*flag == '\0')
		return (1);
	else
		return (0);
}

static int	ft_term_heredoc(int out_fd, char *line)
{
	close(out_fd);
	if (!line)
		ft_putstr_fd("\033[1A> ", 2);
	free(line);
	return (0);
}

int	heredoc_child(t_cmd *here, char *file_name, t_env *env_list)
{
	char	*line;
	int		out_fd;
	int		flag;

	out_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, \
	S_IREAD | S_IWRITE);
	if (out_fd == -1)
		return (-1);
	flag = ft_check_keyword_flag(here->flag);
	ft_interpret_dq_sq(here);
	while (1)
	{
		line = readline("> ");
		if (!line
			|| (here->str[0] && !ft_strncmp(line, here->str, ULONG_MAX)))
			return (ft_term_heredoc(out_fd, line));
		if (flag)
			translate_heredoc(&line, env_list);
		ft_putendl_fd(line, out_fd);
		free(line);
	}
}

int	heredoc_parent(pid_t id)
{
	int	status;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (sig_error(1));
	waitpid(id, &status, 0);
	g_minishell.exit_num = WEXITSTATUS(status);
	if (signal(SIGINT, shell_sig_handler) == SIG_ERR)
		return (sig_error(1));
	return (WEXITSTATUS(status));
}

int	heredoc(t_cmd *here, char *file_name, t_env *env_list)
{
	pid_t	id;

	id = fork();
	g_minishell.exit_num = 0;
	if (id < 0)
	{
		perror("fork");
		return (-1);
	}
	if (id == 0)
	{
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
			exit(sig_error(1));
		if (heredoc_child(here, file_name, env_list) < 0)
		{
			put_error_str("open", NULL, 1);
			exit (2);
		}
		exit(0);
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (sig_error(1));
	return (heredoc_parent(id));
}
