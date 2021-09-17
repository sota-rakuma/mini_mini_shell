/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoatoll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:13:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/08/20 16:06:30 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_digit(long long num)
{
	size_t	digit;

	digit = 0;
	if (!num)
		return (1);
	if (num < 0)
		digit++;
	while (num)
	{
		digit++;
		num /= 10;
	}
	return (digit);
}

char	*ft_lltoa(long long num)
{
	size_t	digit;
	size_t	index;
	char	*str;

	digit = ft_count_digit(num);
	str = (char *)ft_calloc(sizeof(char) * (digit + 1), 1);
	if (!str)
		return (NULL);
	str[digit] = '\0';
	index = 1;
	if (num < 0)
	{
		*str = '-';
		str[digit - index] = (-1) * (num % 10) + '0';
		num /= 10;
		num *= -1;
		index++;
	}
	while ((*str != '-' && index <= digit) || index < digit)
	{
		str[digit - index] = (num % 10) + '0';
		num /= 10;
		index++;
	}
	return (str);
}

static int	is_ok(long long num, int c, int flag)
{
	long int	ov_div;
	long int	ov_mod;
	int			nxt;

	nxt = c - '0';
	if (flag == -1)
	{
		ov_div = LLONG_MAX / 10;
		ov_mod = LLONG_MAX % 10 + 1;
	}
	else
	{
		ov_div = LLONG_MAX / 10;
		ov_mod = LLONG_MAX % 10;
	}
	if ((ov_div < num) || (ov_div == num && ov_mod < nxt))
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	long long	num;
	int			flag;

	flag = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (flag == -1 && is_ok(num, *str, flag))
			return (LLONG_MIN);
		else if (flag == 1 && is_ok(num, *str, flag))
			return (LLONG_MAX);
		num = 10 * num + (*str - '0');
		str++;
	}
	return (num * flag);
}
