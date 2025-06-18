/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:51:04 by skang             #+#    #+#             */
/*   Updated: 2024/10/11 15:52:09 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			loop;
	unsigned char	*s_ptr;

	loop = 0;
	s_ptr = (unsigned char *)s;
	while (loop < n)
	{
		if (*s_ptr == (unsigned char)c)
			return (s_ptr);
		s_ptr++;
		loop++;
	}
	return (NULL);
}
