/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srakuma_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:39:06 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/24 19:53:39 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_first(t_cmd *last)
{
	t_cmd	*first;

	first = last;
	while (first->prev)
		first = first->prev;
	return (first);
}

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
