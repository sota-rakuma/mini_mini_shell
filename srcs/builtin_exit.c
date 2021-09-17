/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:21:58 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/02 21:47:03 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_exit_flag(const char *str, long long *num)
{
	char	*ll_limits;
	size_t	index;

	if (!str)
		return (0);
	ll_limits = ft_lltoa(*num);
	index = 0;
	if (!ll_limits)
		ft_exit(EXIT_FAILURE);
	while (*str)
	{
		if (*str == ll_limits[index])
			index++;
		else if ((!ft_isspace(*str) && *str != '+')
			|| (ft_isdigit(*str) && *str != ll_limits[index]))
		{
			if (*num == LLONG_MIN)
				*num = LLONG_MAX;
			return (1);
		}
		str++;
	}
	free(ll_limits);
	return (0);
}

static void	ft_exit_with_num(t_cmd *cmd, t_env *env_list, long long num, \
				int flag)
{
	if (flag)
	{
		ft_putstr_fd("exit : ", 2);
		put_error_str(cmd->next->str, "numeric argument required", 0);
		num = 255;
	}
	ft_free_all_bidir_lst(env_list);
	ft_port_free_cmd(cmd, NULL, 0);
	ft_exit(num);
}

int	exit_cmd(t_env *env_list, t_cmd *cmd)
{
	long long	num;
	int			flag;

	flag = 0;
	ft_putendl_fd("exit", 1);
	if (cmd->next)
	{
		num = ft_atoll(cmd->next->str);
		flag = ft_set_exit_flag(cmd->next->str, &num);
		if (!flag && cmd->next->next)
		{
			put_error_str("exit", "too many arguments", 0);
			return (1);
		}
	}
	else
		num = g_minishell.exit_num;
	num %= 256;
	ft_exit_with_num(cmd, env_list, num, flag);
	return (0);
}
