/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:14:31 by takataok          #+#    #+#             */
/*   Updated: 2021/09/01 16:19:47 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char a, char character)
{
	if (character == a)
		return (0);
	else
		return (1);
}

static char	**set_answer_memo(const char *str, char character)
{
	int	i;
	int	count;

	i = -1;
	count = 1;
	while (str[++i] != '\0')
	{
		if (str[i] == character)
		{
			count++;
			continue ;
		}
	}
	return ((char **)malloc((count + 1) * (sizeof(char *))));
}

static int	ft_split_str(char **answer, const char *str, char character)
{
	int		i;
	int		j;
	int		head;

	i = -1;
	j = -1;
	head = 0;
	while (++i <= (int)ft_strlen(str))
	{
		if (check(str[i], character) == 0 || str[i] == '\0')
		{
			if (head == i)
				answer[++j] = ft_strdup(".");
			else
				answer[++j] = ft_substr(str, head, i - head);
			if (answer[j] == NULL)
				return (-2);
			answer[j + 1] = NULL;
			head = i + 1;
		}
	}
	return (j);
}

char	**ft_split_path(const char *str, char character)
{
	char	**answer;
	int		count;

	if (str == NULL)
		return (NULL);
	answer = set_answer_memo(str, character);
	if (answer == NULL)
		return (NULL);
	count = ft_split_str(answer, str, character);
	if (count == -2)
	{
		count = -1;
		while (answer[++count] != NULL)
			free(answer[count]);
		free(answer);
		return (NULL);
	}
	else if (count == -1)
		answer[count + 1] = NULL;
	return (answer);
}
