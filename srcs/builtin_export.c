/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:44:45 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/26 15:13:34 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_minlst(t_env *env_list, t_env *limit)
{
	size_t			key_len;
	t_env			*target;
	unsigned char	min[BUFSIZ];

	target = env_list;
	min[0] = 255;
	while (target)
	{
		key_len = ft_strlen(target->key);
		if (ft_memcmp(target->key, min, key_len + 1) < 0)
		{
			if (!limit)
				ft_memcpy(min, target->key, ft_strlen(target->key) + 1);
			else if (limit
				&& ft_memcmp(limit->key, target->key, key_len + 1) < 0)
				ft_memcpy(min, target->key, ft_strlen(target->key) + 1);
		}
		target = target->next;
	}
	return (search_key(env_list, (char *)min));
}

int	sorted_print(t_env *env_list)
{
	size_t	lst_len;
	t_env	*min;
	t_env	*limit;

	lst_len = ft_bidir_lst_size(env_list);
	limit = NULL;
	while (lst_len--)
	{
		min = get_minlst(env_list, limit);
		if (min->var)
			printf("%s=\"%s\"\n", min->key, min->var);
		else
			printf("%s\n", min->key);
		limit = min;
	}
	return (0);
}

int	export_cmd(t_env *env_list, t_cmd *cmd)
{
	char	*key;
	char	*value;
	t_cmd	*target;

	if (!cmd)
		return (sorted_print(env_list));
	target = cmd;
	while (target)
	{
		key = NULL;
		value = NULL;
		if (set_key_value(target->str, &key, &value) || !ft_check_enval(key))
		{
			ft_free_pointer(key, value, NULL, NULL);
			return (print_error_strings("minishell: export: `", target->str, \
				"': not a valid identifier"));
		}
		if (key)
			rewrite_envlist(env_list, key, value);
		ft_free_pointer(key, value, NULL, NULL);
		target = target->next;
	}
	return (0);
}
