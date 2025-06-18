/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:01 by skang             #+#    #+#             */
/*   Updated: 2024/10/16 15:12:10 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	index;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	index = dest_len;
	dest += dest_len;
	while ((index + 1) < size && *src != '\0')
	{
		*(dest++) = *(src++);
		index++;
	}
	*dest = '\0';
	if (dest_len < size)
		return (dest_len + src_len);
	else
		return (src_len + size);
}
