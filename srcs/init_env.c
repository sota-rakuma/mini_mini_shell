/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 20:37:33 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/02 22:02:15 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_new_env(void)
{
	t_env	*env_list;
	char	buff[PATH_MAX];

	env_list = NULL;
	ft_memset(buff, '\0', PATH_MAX);
	if (!getcwd(buff, PATH_MAX))
	{
		put_error_str("getcwd", NULL, 1);
		return (NULL);
	}
	ft_bidir_lst_add_back(&env_list, "OLDPWD", NULL);
	ft_bidir_lst_add_back(&env_list, "PWD", buff);
	return (env_list);
}

char	*ft_get_shlvl(int level)
{
	if (level == 999)
		return (ft_strdup(""));
	else if (level > 999)
	{
		ft_putstr_fd("bash: warning: shell level (", 2);
		ft_putnbr_fd(level + 1, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		return (ft_strdup("1"));
	}
	else if (level < 0)
		return (ft_strdup("0"));
	return (ft_itoa(level + 1));
}

static int	ft_check_shlvl(t_env *shlvl)
{
	char	*tmp;
	size_t	len;

	if (!shlvl || !shlvl->var)
		return (0);
	tmp = shlvl->var;
	len = ft_strlen(tmp);
	while (ft_isdigit(*tmp))
		tmp++;
	if ((size_t)(tmp - shlvl->var) != len)
		return (0);
	return (1);
}

int	ft_incliment_shlvl(t_env **env_list)
{
	int		level;
	int		flag;
	t_env	*shlvl;

	shlvl = search_key(*env_list, "SHLVL");
	flag = ft_check_shlvl(shlvl);
	if (!flag && !shlvl)
		ft_bidir_lst_add_back(env_list, "SHLVL", "1");
	else
	{
		if (shlvl->var)
			level = ft_atoi(shlvl->var);
		else
			level = 0;
		free(shlvl->var);
		shlvl->var = ft_get_shlvl(level);
		if (!shlvl || !shlvl->var)
			return (0);
	}
	return (1);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env_list;

	if (!(*envp))
		env_list = ft_get_new_env();
	else
		env_list = set_envlist(envp);
	if (env_list == NULL)
		return (NULL);
	if (!ft_incliment_shlvl(&env_list))
		return (NULL);
	ft_set_pwd(NULL, 0);
	return (env_list);
}
