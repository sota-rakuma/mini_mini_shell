/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:40:55 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/27 18:39:08 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expnaded_str(char *old_str, char *new, char *old, size_t index)
{
	char	*new_port;
	char	*old_port;
	char	*new_str;

	new_port = replace_str(old_str + index, old, new, 1);
	if (index)
		old_port = ft_substr(old_str, 0, index);
	else
		old_port = ft_strdup("\0");
	if (!old_port)
		ft_exit (EXIT_FAILURE);
	if (index)
		new_str = ft_strjoin(old_port, new_port);
	else
		new_str = ft_strjoin(new_port, old_port);
	free(old_port);
	free(new_port);
	return (new_str);
}

void	ft_change_flag(t_cmd *target, size_t old_len, size_t new_len, \
	size_t index)
{
	char	*new;
	char	*old;
	char	*old_flag;

	old_flag = target->flag;
	new = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new)
		ft_exit(EXIT_FAILURE);
	new[new_len] = '\0';
	ft_memset(new, old_flag[index], new_len);
	old = ft_substr(target->flag, index, old_len);
	if (!old)
		ft_exit(EXIT_FAILURE);
	target->flag = get_expnaded_str(old_flag, new, old, index);
	if (!target->flag)
		ft_exit(EXIT_FAILURE);
	free(old_flag);
	free(old);
	free(new);
}
