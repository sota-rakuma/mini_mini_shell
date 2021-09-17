/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 01:02:57 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/02 21:46:17 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_set_pwd(char *dir, int flag)
{
	static char	buf[PATH_MAX];
	char		*pwd;

	if (flag == 1)
	{
		pwd = ft_strdup(buf);
		if (!pwd)
			ft_exit(EXIT_FAILURE);
		return (pwd);
	}
	if (dir == NULL)
	{
		if (!getcwd(buf, PATH_MAX))
		{
			perror("minishell_init: getcwd");
			ft_memset(buf, '\0', PATH_MAX);
		}
	}
	else
		ft_strlcpy(buf, dir, PATH_MAX);
	return (NULL);
}

int	echo_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		flag;

	flag = 0;
	tmp = cmd;
	if (tmp && !ft_strncmp(tmp->str, "-n", 3))
	{
		flag = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->str, 1);
		tmp = tmp->next;
		if (tmp)
			write(1, " ", 1);
	}
	if (!cmd || (!flag && cmd))
		write(1, "\n", 1);
	return (0);
}

int	pwd_cmd(t_env *env_list)
{
	char	*buff;

	(void)env_list;
	buff = ft_set_pwd(NULL, 1);
	if (!(*buff))
	{
		perror("getcwd");
		free(buff);
		return (1);
	}
	ft_putendl_fd(buff, 1);
	free(buff);
	return (0);
}
