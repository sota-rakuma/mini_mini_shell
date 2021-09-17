/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srakuma_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 19:52:48 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/26 00:11:29 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bilst	*ft_bidir_lst_new(char *key, char *value)
{
	t_bilst	*new;
	int		flag;

	flag = 1;
	new = (t_bilst *)malloc(sizeof(t_bilst));
	if (!new)
		ft_exit(EXIT_FAILURE);
	new->key = ft_strdup(key);
	if (!new->key)
		ft_exit(EXIT_FAILURE);
	new->var = NULL;
	if (value)
		new->var = ft_strdup(value);
	else
		flag = 0;
	if (flag && !new->var)
		ft_exit(EXIT_FAILURE);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_bilst	*ft_bidir_lst_last(t_bilst *env_list)
{
	t_bilst	*tmp;

	tmp = env_list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_bidir_lst_add_back(t_bilst **bidir_list, char *key, char *value)
{
	t_bilst	*new;
	t_bilst	*last;

	new = ft_bidir_lst_new(key, value);
	if (*bidir_list)
	{
		last = ft_bidir_lst_last(*bidir_list);
		last->next = new;
		new->prev = last;
		return ;
	}
	*bidir_list = new;
}

size_t	ft_bidir_lst_size(t_bilst *bilist)
{
	size_t	len;
	t_bilst	*tmp;

	len = 0;
	tmp = bilist;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
