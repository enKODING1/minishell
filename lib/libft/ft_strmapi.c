/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:09:31 by skang             #+#    #+#             */
/*   Updated: 2024/10/15 14:58:51 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	s_len;
	int		index;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	index = 0;
	ptr = (char *)malloc(s_len + 1);
	if (!ptr)
		return (NULL);
	while (s[index] != '\0')
	{
		ptr[index] = f(index, s[index]);
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}
