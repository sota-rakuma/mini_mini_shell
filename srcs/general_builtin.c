/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 01:05:18 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/02 21:57:50 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_cmd(t_env **env_list, t_cmd *cmd)
{
	int	res;

	res = -1;
	if (!ft_strncmp(cmd->str, "export", 7))
		res = export_cmd(*env_list, cmd->next);
	else if (!ft_strncmp(cmd->str, "unset", 6))
		res = unset_cmd(env_list, cmd->next);
	else if (!ft_strncmp(cmd->str, "echo", 5))
		res = echo_cmd(cmd->next);
	else if (!ft_strncmp(cmd->str, "exit", 5))
		res = exit_cmd(*env_list, cmd);
	else if (!ft_strncmp(cmd->str, "env", 4))
		res = env_cmd(*env_list);
	else if (!ft_strncmp(cmd->str, "pwd", 4))
		res = pwd_cmd(*env_list);
	else if (!ft_strncmp(cmd->str, "cd", 3))
		res = cd_cmd(env_list, cmd->next);
	return (res);
}
