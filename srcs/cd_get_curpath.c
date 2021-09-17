/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_curpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:43:12 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/03 22:50:22 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_stat_dir(char *tmp, char *end, char **prefix)
{
	int			flag;
	struct stat	buf;

	flag = stat(tmp, &buf);
	if (!flag || !(*end))
	{
		*prefix = tmp;
		if (!(*prefix))
			ft_exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}

int	ft_try_cat_dir(char *cdpath, char *dir_ope, char **prefix)
{
	int			flag;
	char		*start;
	char		*end;
	char		*tmp;

	start = cdpath;
	tmp = (char *)ft_calloc(PATH_MAX, sizeof(char));
	flag = 0;
	while (!flag)
	{
		end = ft_strchr(start, ':');
		if (!end)
			end = cdpath + ft_strlen(cdpath);
		ft_strlcpy(tmp, start, end - start + 1);
		if (end != cdpath && *(end - 1) != '/')
			ft_strlcat(tmp, "/", PATH_MAX);
		ft_strlcat(tmp, dir_ope, PATH_MAX);
		flag = ft_check_stat_dir(tmp, end, prefix);
		start = end + 1;
	}
	return (flag);
}

static void	ft_cat_prefix(char buff[], char *dir_ope)
{
	size_t	len;
	char	*dir;

	len = ft_strlen(buff);
	if (!len)
		ft_strlcpy(buff, dir_ope, PATH_MAX);
	else if (buff[len - 1] != '/')
		ft_strlcat(buff, "/", PATH_MAX);
	dir = ft_strdup(buff);
	if (!dir)
		ft_exit(EXIT_FAILURE);
	ft_strlcpy(buff, "./", PATH_MAX);
	ft_strlcat(buff, dir, PATH_MAX);
	free(dir);
}

int	ft_get_curpath(t_env *env_list, char *dir_ope, char buff[])
{
	t_env	*cdpath;
	char	*prefix;

	cdpath = search_key(env_list, "CDPATH");
	prefix = NULL;
	if (dir_ope[0] != '/' && dir_ope[0] != '.'
		&& cdpath && cdpath->var && *(cdpath->var))
	{
		ft_try_cat_dir(cdpath->var, dir_ope, &prefix);
		if (prefix)
		{
			ft_strlcpy(buff, prefix, PATH_MAX);
			free(prefix);
		}
	}
	if (buff[0] != '/' && dir_ope[0] != '/' && dir_ope[0] != '.')
		ft_cat_prefix(buff, dir_ope);
	else if (!buff[0])
		ft_strlcpy(buff, dir_ope, PATH_MAX);
	return (1);
}
