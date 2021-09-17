/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 22:45:55 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/22 22:39:12 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion_param(t_cmd *target, t_env *env_list)
{
	size_t	dptr_len;
	size_t	i;
	char	*dollar_ptr;
	char	*pre_dollar_ptr;

	dollar_ptr = ft_strchr(target->str, '$');
	i = 0;
	while (dollar_ptr)
	{
		dptr_len = (dollar_ptr - target->str) / sizeof(char);
		if (dollar_ptr && target->flag[dptr_len] != '2'
			&& (dollar_ptr[1] == '?' || ((!ft_isdigit(dollar_ptr[1])
						&& is_env_val_ele(dollar_ptr[1])))))
			dollar_expansion(target, dptr_len, dollar_ptr, env_list);
		pre_dollar_ptr = dollar_ptr;
		dollar_ptr = ft_strchr(target->str, '$');
		if (dollar_ptr == pre_dollar_ptr)
		{
			i += ft_vallen(dollar_ptr);
			dollar_ptr = ft_strchr(dollar_ptr + i, '$');
		}
	}
}

t_cmd	*ft_remake_cmd(t_cmd *target, size_t pre_index, size_t index)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		ft_exit(EXIT_FAILURE);
	new->str = ft_substr(target->str, pre_index, index - pre_index);
	if (!new->str)
		ft_exit(EXIT_FAILURE);
	new->flag = ft_substr(target->flag, pre_index, index - pre_index);
	if (!new->flag)
		ft_exit(EXIT_FAILURE);
	new->next = NULL;
	new->prev = NULL;
	new->tmp_name = NULL;
	return (new);
}

t_cmd	*ft_remove_target(t_cmd *target, t_cmd *new)
{
	t_cmd	*last;

	last = NULL;
	if (!new)
	{
		last = target->prev;
		if (last)
			last->next = target->next;
		if (target->next)
			target->next->prev = last;
	}
	else
	{
		if (target->prev)
			target->prev->next = new;
		new->prev = target->prev;
		last = ft_cmd_last(new);
		if (target->next)
			target->next->prev = last;
		last->next = target->next;
	}
	ft_free_pointer(target->str, target->flag, target, NULL);
	return (last);
}

t_cmd	*ft_wordspliting(t_cmd *target)
{
	t_cmd	*new;
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	new = NULL;
	len = ft_strlen(target->str);
	while (start <= len)
	{
		while (target->str[start]
			&& ft_isspace(target->str[start]) && target->flag[start] == '1')
			start++;
		end = start;
		while (target->str[end] && ((ft_isspace(target->str[end])
					&& target->flag[end] != '1')
				|| !ft_isspace(target->str[end])))
			end++;
		if (!start && end == len)
			return (target);
		else if (start < end)
			add_cmd(&new, ft_remake_cmd(target, start, end));
		start = ++end;
	}
	return (new);
}

void	translate_string(t_cmd **cmd, t_env *env_list)
{
	t_cmd	*target;
	t_cmd	*new;
	t_cmd	*tmp;

	target = *cmd;
	tmp = NULL;
	while (target)
	{
		expansion_param(target, env_list);
		ft_interpret_dq_sq(target);
		new = ft_wordspliting(target);
		tmp = target->next;
		if (target != new)
		{
			target = ft_remove_target(target, new);
			if (!target)
				*cmd = tmp;
			else if (new && !new->prev)
				*cmd = new;
		}
		target = tmp;
	}
}
