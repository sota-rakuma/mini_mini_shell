/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canonicalisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:48:50 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/03 23:08:21 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_str_pre_sla_len(char *first, char *dot)
{
	size_t	len;

	while (dot != first && *dot != '/')
		dot--;
	len = 0;
	while (*dot == '/' && dot - 1 != first && *(dot - 1) == '/')
	{
		len++;
		dot--;
	}
	while (dot != first && dot - 1 != first)
	{
		len++;
		dot--;
		if (*dot == '/')
			break ;
	}
	return (len);
}

static void	ft_remove_slash(char *first)
{
	size_t	len;
	char	*slash;

	slash = ft_strchr(first, '/');
	while (slash)
	{
		len = 1;
		while (slash[len] == '/')
			len++;
		if (len > 0)
			ft_memmove(slash, slash + (len - 1), ft_strlen(slash));
		slash = ft_strchr(slash + 1, '/');
	}
	len = ft_strlen(first);
	if (len > 1 && first[len - 1] == '/')
		first[len - 1] = '\0';
}

static void	ft_remove_dot(char buff[], char *first)
{
	char	*dot;
	size_t	len;

	first = buff;
	dot = ft_strchr(buff, '.');
	while (dot)
	{
		buff = dot;
		if (!buff[1] || buff[1] == '/')
			ft_memmove(buff, buff + 1, ft_strlen(buff + 1) + 1);
		else if (buff[1] == '.' && (!buff[2] || buff[2] == '/'))
		{
			len = ft_str_pre_sla_len(first, buff);
			ft_memmove(buff - len, buff + 2, ft_strlen(buff + 2) + 1);
			buff -= len;
		}
		else
			buff++;
		dot = ft_strchr(buff, '.');
	}
}

void	ft_get_canonical_form(char buff[])
{
	char	*first;

	first = buff;
	ft_remove_dot(buff, first);
	ft_remove_slash(first);
}
