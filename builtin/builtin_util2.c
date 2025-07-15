/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:53:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 01:04:23 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_arglen(char **argv)
{
	int	i;

	i = 0;
	if (argv[0] == NULL)
		return (0);
	while (argv[i] != NULL)
		i++;
	return (i);
}

void	two_free(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}
