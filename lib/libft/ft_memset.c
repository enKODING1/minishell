/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:37:57 by skang             #+#    #+#             */
/*   Updated: 2024/10/15 14:59:15 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			loop;
	unsigned char	*ptr;
	unsigned char	value;

	loop = 0;
	ptr = (unsigned char *)dest;
	value = (unsigned char)c;
	while (loop < count)
	{
		ptr[loop] = value;
		loop++;
	}
	return (dest);
}
