/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:00 by skang             #+#    #+#             */
/*   Updated: 2024/10/07 15:55:13 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_length(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	recursion_itoa(char *dest, long n, int len)
{
	if (n >= 10)
	{
		recursion_itoa(dest, n / 10, len - 1);
		dest[len] = (n % 10) + '0';
		return ;
	}
	dest[len] = n + '0';
	return ;
}

char	*ft_itoa(int n)
{
	char	*result;
	int		n_len;
	long	new_n;

	new_n = (long)n;
	n_len = get_int_length(new_n);
	result = (char *)malloc(n_len + 1);
	if (result == NULL)
		return (NULL);
	if (new_n < 0)
	{
		*result = '-';
		new_n *= -1;
	}
	recursion_itoa(result, new_n, n_len - 1);
	result[n_len] = '\0';
	return (result);
}
