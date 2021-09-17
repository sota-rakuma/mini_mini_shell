/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:04:06 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/27 01:07:21 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_error(int num)
{
	put_error_str("signal", NULL, 1);
	return (num);
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(128 + SIGINT);
}

int	proc_child_stop_by_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(SIGQUIT, 2);
	}
	write(1, "\n", 1);
	return (128 + sig);
}

void	shell_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
