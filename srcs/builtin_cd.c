/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:49:41 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/03 22:51:21 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cd_error(t_cmd *cmd)
{
	if (cmd && ft_strlen(cmd->str) > NAME_MAX)
	{
		ft_putstr_fd("minishsell: cd: ", 2);
		ft_putstr_fd(cmd->str, 2);
		ft_putendl_fd(": File name too long", 2);
		return (1);
	}
	return (0);
}

int	ft_mv_to_home(t_env *env_list)
{
	t_env	*home;
	char	old_pwd[PATH_MAX];

	home = search_key(env_list, "HOME");
	if (!home)
	{
		put_error_str("cd", "HOME not set", 0);
		return (1);
	}
	if (!getcwd(old_pwd, PATH_MAX) || chdir(home->var) == -1)
	{
		put_error_str("cd", NULL, 1);
		return (1);
	}
	rewrite_envlist(env_list, "OLDPWD", old_pwd);
	ft_set_pwd(home->var, 0);
	rewrite_envlist(env_list, "PWD", home->var);
	return (0);
}

int	ft_exec_chdir(t_cmd *cmd, char curpath[], char *pwd)
{
	if (chdir(curpath) == -1)
	{
		if (chdir(cmd->str) == -1)
		{
			free(pwd);
			ft_putstr_fd("minishell: cd: ", 2);
			perror(cmd->str);
			return (0);
		}
		if (getcwd(curpath, PATH_MAX) == NULL)
		{
			put_error_str("cd: getcwd", NULL, 1);
			ft_strlcpy(curpath, pwd, PATH_MAX);
			if (curpath[ft_strlen(curpath) - 1] != '/')
				ft_strlcat(curpath, "/", PATH_MAX);
			ft_strlcat(curpath, cmd->str, PATH_MAX);
		}
	}
	return (1);
}

static int	ft_set_curpath(t_cmd *cmd, t_env *env_list, char curpath[], \
				char *pwd)
{
	char	*tmp;

	if (!ft_get_curpath(env_list, cmd->str, curpath))
		return (1);
	if (curpath[0] != '/')
	{
		tmp = ft_strdup(curpath);
		if (!tmp)
			ft_exit(EXIT_FAILURE);
		ft_strlcpy(curpath, pwd, PATH_MAX);
		ft_strlcat(curpath, "/", PATH_MAX);
		ft_strlcat(curpath, tmp, PATH_MAX);
		free(tmp);
	}
	ft_get_canonical_form(curpath);
	return (0);
}

int	cd_cmd(t_env **env_list, t_cmd *cmd)
{
	char	*pwd;
	char	curpath[PATH_MAX];

	if (ft_check_cd_error(cmd))
		return (1);
	if (!cmd)
		return (ft_mv_to_home(*env_list));
	ft_memset(curpath, '\0', PATH_MAX);
	pwd = ft_set_pwd(NULL, 1);
	if (ft_set_curpath(cmd, *env_list, curpath, pwd))
		return (1);
	if (!curpath[0])
	{
		free(pwd);
		return (0);
	}
	if (!ft_exec_chdir(cmd, curpath, pwd))
		return (1);
	ft_set_pwd(curpath, 0);
	rewrite_envlist(*env_list, "OLDPWD", pwd);
	rewrite_envlist(*env_list, "PWD", curpath);
	free(pwd);
	return (0);
}
