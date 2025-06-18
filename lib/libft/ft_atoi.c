/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:17:24 by skang             #+#    #+#             */
/*   Updated: 2024/10/11 13:39:52 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int n)
{
	return ((n >= 8 && n <= 13) || n == 32);
}

static int	is_operator(char c)
{
	return (c == '+' || c == '-');
}

static int	is_num(char n)
{
	return (n >= '0' && n <= '9');
}

int	ft_atoi(const char *nptr)
{
	int	operator;
	int	result;

	operator = 1;
	result = 0;
	while (is_space(*nptr))
		nptr++;
	if (is_operator(*nptr))
	{
		if (*nptr == '-')
			operator = -1;
		nptr++;
	}
	while (is_num(*nptr))
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	return (result * operator);
}
