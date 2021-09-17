/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_dollar_quotation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:27:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/27 18:45:57 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_dq_sq(t_cmd *target, char *ptr_1)
{
	size_t	new_len;
	char	*tmp;
	char	*ptr_2;

	ptr_2 = ft_strchr(ptr_1 + 1, *ptr_1);
	if (!ptr_2)
		ft_exit(EXIT_FAILURE);
	ft_change_flag(target, 1, 0, (ptr_1 - target->str) / sizeof(char));
	ft_change_flag(target, 1, 0, ((ptr_2 - 1) - target->str) / sizeof(char));
	new_len = (size_t)((ptr_1 - target->str) + (ptr_2 - ptr_1 - 1) + \
		target->str + (ft_strlen(target->str) - 1) - ptr_2) / sizeof(char);
	tmp = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!tmp)
		ft_exit(EXIT_FAILURE);
	ft_strncpy(tmp, target->str, ptr_1 - target->str);
	ft_strlcat(tmp, ptr_1 + 1, ((ptr_1 - target->str) + (ptr_2 - ptr_1)) \
		/ sizeof(char));
	ft_strlcat(tmp, ptr_2 + 1, new_len + 1);
	free(target->str);
	target->str = tmp;
}

int	ft_determine_if_remove(t_cmd *target, char *dq, char *sq)
{
	if (dq && target->flag[(dq - target->str) / sizeof(char)] == '3')
	{
		ft_remove_dq_sq(target, dq);
		return (1);
	}
	else if (sq && target->flag[(sq - target->str) / sizeof(char)] == '2')
	{
		ft_remove_dq_sq(target, sq);
		return (1);
	}
	return (0);
}

void	ft_interpret_dq_sq(t_cmd *target)
{
	size_t	diff;
	char	*dq_ptr;
	char	*sq_ptr;

	diff = 0;
	dq_ptr = ft_strchr(target->str, '\"');
	sq_ptr = ft_strchr(target->str, '\'');
	while (dq_ptr || sq_ptr)
	{
		diff++;
		if (ft_determine_if_remove(target, dq_ptr, sq_ptr))
			diff = 0;
		dq_ptr = ft_strchr(target->str + diff, '\"');
		sq_ptr = ft_strchr(target->str + diff, '\'');
	}
}

size_t	ft_subsutitute_str(t_cmd *target, t_env *value, char *val, \
			size_t index)
{
	size_t	len;
	char	*old_str;
	char	*tmp;

	old_str = target->str;
	if (value)
	{
		target->str = get_expnaded_str(old_str, value->var, val, index);
		return (ft_strlen(value->var));
	}
	else if (val[1] == '?')
	{
		tmp = ft_itoa(g_minishell.exit_num);
		if (!tmp)
			ft_exit(EXIT_FAILURE);
		target->str = get_expnaded_str(old_str, tmp, val, index);
		len = ft_strlen(tmp);
		free(tmp);
		return (len);
	}
	target->str = get_expnaded_str(old_str, "\0", val, index);
	return (0);
}

void	dollar_expansion(t_cmd *target, size_t dindex, char *dollar_ptr, \
			t_env *env_list)
{
	size_t	new_len;
	t_env	*value;
	char	*old_str;
	char	*str;

	str = ft_get_key_in_str(target, dollar_ptr);
	if (!str)
		ft_exit(EXIT_FAILURE);
	old_str = target->str;
	value = search_key(env_list, str + 1);
	if (value && !value->var)
	{
		value->var = ft_strdup("");
		if (!value->var)
			ft_exit(EXIT_FAILURE);
		new_len = ft_subsutitute_str(target, value, str, dindex);
		free(value->var);
		value->var = NULL;
	}
	else
		new_len = ft_subsutitute_str(target, value, str, dindex);
	ft_change_flag(target, ft_strlen(str), new_len, dindex);
	free(old_str);
	free(str);
}
