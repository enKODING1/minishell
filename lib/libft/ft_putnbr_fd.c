/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:30:09 by skang             #+#    #+#             */
/*   Updated: 2024/10/15 14:58:13 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recursion(long n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_recursion(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
		return ;
	}
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	new_n;

	new_n = (long)n;
	if (new_n < 0)
	{
		new_n *= -1;
		ft_putchar_fd('-', fd);
	}
	ft_putnbr_recursion(new_n, fd);
}
