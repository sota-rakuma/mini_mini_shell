/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srakuma_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:57:24 by srakuma           #+#    #+#             */
/*   Updated: 2021/09/03 17:01:34 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_val_ele(int c)
{
	return (ft_isalnum(c) || c == '_');
}

size_t	ft_vallen(char *dollar_ptr)
{
	size_t	len;

	len = 0;
	if (*dollar_ptr == '$')
		len++;
	if (dollar_ptr[len] == '?')
		return (2);
	while (is_env_val_ele(dollar_ptr[len]))
		len++;
	return (len);
}

static int	ft_cnt_appearance(char *haystack, char *needle)
{
	int		times;
	size_t	index;
	size_t	needle_len;
	size_t	haystack_len;

	index = 0;
	times = 0;
	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	while (index < haystack_len)
	{
		if (ft_strnstr(haystack + index, needle, ft_strlen(haystack + index)))
		{
			times++;
			index += needle_len;
		}
		index++;
	}
	return (times);
}

char	*replace_str(char *haystack, char *old, char *new, int times)
{
	size_t	index;
	size_t	old_len;
	size_t	dstsize;
	char	*ptr;
	char	*new_str;

	old_len = ft_strlen(old);
	if (times <= 0)
		times = ft_cnt_appearance(haystack, old);
	dstsize = ft_strlen(haystack) - (old_len - ft_strlen(new)) * times;
	new_str = (char *)ft_calloc(dstsize + 1, sizeof(char));
	if (!new_str)
		ft_exit(EXIT_FAILURE);
	index = 0;
	ptr = ft_strnstr(haystack, old, ft_strlen(haystack));
	while (times-- && ptr)
	{
		ft_strncpy(new_str + ft_strlen(new_str), haystack + index, \
			(ptr - (haystack + index)) / sizeof(char));
		ft_strlcat(new_str, new, dstsize + 1);
		index = ((ptr - haystack) / sizeof(char)) + old_len;
		ptr = ft_strnstr(haystack + index, old, ft_strlen(haystack + index));
	}
	ft_strlcat(new_str, haystack + index, dstsize + 1);
	return (new_str);
}

char	*ft_get_key_in_str(t_cmd *target, char *dollar_ptr)
{
	size_t	dq_len;
	size_t	dollar_index;
	size_t	index;
	char	*str;

	index = 0;
	index = ft_vallen(dollar_ptr);
	dollar_index = (dollar_ptr - target->str) / sizeof(char);
	dq_len = 0;
	while (target->flag[dollar_index + 1]
		&& target->flag[dollar_index] == target->flag[dollar_index + 1])
	{
		dq_len++;
		dollar_index++;
	}
	if (dq_len + 1 < index)
		index = dq_len + 1;
	str = ft_substr(dollar_ptr, 0, index);
	if (!str)
		ft_exit(EXIT_FAILURE);
	return (str);
}
