/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:43:04 by skang             #+#    #+#             */
/*   Updated: 2024/10/15 14:58:27 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup_s;
	size_t	s_len;
	size_t	index;

	s_len = ft_strlen(s);
	dup_s = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dup_s == NULL)
		return (NULL);
	index = 0;
	while (index < s_len)
	{
		dup_s[index] = s[index];
		index++;
	}
	dup_s[index] = '\0';
	return (dup_s);
}
