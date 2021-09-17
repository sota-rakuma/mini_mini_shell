/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 02:48:12 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/03 20:54:53 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bilst	*search_key(t_bilst *bi_list, const char *str)
{
	t_bilst	*tmp;

	if (!str)
		return (NULL);
	tmp = bi_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_key_value(char *str, char **key, char **value)
{
	size_t	eq_p_len;
	char	*eq_p;

	eq_p = ft_strchr(str, '=');
	*key = NULL;
	*value = NULL;
	if (eq_p)
	{
		eq_p_len = ft_strlen(eq_p);
		if ((str == eq_p) || *(eq_p - 1) == ' ')
			return (1);
		else if (*(eq_p + 1) == '\0')
			*value = ft_strdup("\0");
		else
			*value = ft_substr(eq_p + 1, 0, eq_p_len - 1);
		if (!(*value))
			ft_exit(EXIT_FAILURE);
		*key = ft_substr(str, 0, ft_strlen(str) - eq_p_len);
	}
	else
		*key = ft_strdup(str);
	if (!(*key))
		ft_exit(EXIT_FAILURE);
	return (0);
}

t_env	*set_envlist(char **envp)
{
	t_env	*env_list;
	t_env	*prev;
	t_env	*new;
	char	*key;
	char	*value;

	set_key_value(*envp, &key, &value);
	env_list = ft_bidir_lst_new(key, value);
	ft_free_pointer(key, value, NULL, NULL);
	envp++;
	prev = env_list;
	while (*envp)
	{
		set_key_value(*envp, &key, &value);
		new = ft_bidir_lst_new(key, value);
		new->prev = prev;
		prev->next = new;
		ft_free_pointer(key, value, NULL, NULL);
		envp++;
		prev = new;
	}
	return (env_list);
}

void	rewrite_envlist(t_env *env_list, char *key, char *var)
{
	t_env	*last;
	t_env	*target;

	target = search_key(env_list, key);
	if (target)
	{
		if (var)
		{
			free(target->var);
			target->var = ft_strdup(var);
		}
		if (var && !target->var)
			ft_exit(EXIT_FAILURE);
		return ;
	}
	target = ft_bidir_lst_new(key, var);
	last = ft_bidir_lst_last(env_list);
	last->next = target;
	target->prev = last;
}
