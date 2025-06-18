/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:25:33 by skang             #+#    #+#             */
/*   Updated: 2024/10/01 16:48:19 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	loop;
	int	c_addr;

	loop = 0;
	c_addr = -1;
	while (s[loop] != '\0')
	{
		if (s[loop] == c)
			c_addr = loop;
		loop++;
	}
	if (s[loop] == c)
		c_addr = loop;
	if (c_addr == -1)
		return (NULL);
	return ((char *)s + c_addr);
}
