/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:52:21 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/26 15:11:43 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_enval(char *key)
{
	size_t	index;

	index = 0;
	if (!(*key))
		return (1);
	if (ft_isdigit(*key) || !is_env_val_ele(*key))
		return (0);
	while (key[++index])
	{
		if (!is_env_val_ele(key[index]))
			return (0);
	}
	return (1);
}

int	print_error_strings(char *message_1, char *message_2, char *message_3)
{
	ft_putstr_fd(message_1, 2);
	ft_putstr_fd(message_2, 2);
	ft_putendl_fd(message_3, 2);
	return (1);
}

int	unset_cmd(t_env **env_list, t_cmd *cmd)
{
	t_env	*target;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		target = search_key(*env_list, tmp->str);
		if (!ft_check_enval(tmp->str))
			return (print_error_strings("minishell: unset: `", tmp->str, \
				"': not a valid identifier"));
		tmp = tmp->next;
		if (!target)
			continue ;
		if (target->next)
			target->next->prev = target->prev;
		if (target->prev)
			target->prev->next = target->next;
		else
			*env_list = target->next;
		ft_free_pointer(target->key, target->var, target, NULL);
	}
	return (0);
}

int	env_cmd(t_env *env_list)
{
	t_env	*tmp_env;

	tmp_env = env_list;
	while (tmp_env)
	{
		if (tmp_env->var)
		{
			printf("%s=", tmp_env->key);
			printf("%s\n", tmp_env->var);
		}
		tmp_env = tmp_env->next;
	}
	return (0);
}
