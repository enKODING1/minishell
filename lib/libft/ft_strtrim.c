/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:12:20 by skang             #+#    #+#             */
/*   Updated: 2024/10/15 15:06:53 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_ptr;
	int		front;
	int		rear;

	if (!s1 || !set)
		return (NULL);
	s1_ptr = (char *)s1;
	front = 0;
	rear = (int)ft_strlen(s1_ptr) - 1;
	while (ft_strchr(set, s1_ptr[front]))
		front++;
	while (ft_strchr(set, s1_ptr[rear]))
		rear--;
	if (rear < front)
		return (ft_strdup(""));
	return (ft_substr(s1_ptr, front, rear - front + 1));
}
