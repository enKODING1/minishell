/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:33:32 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/12 01:35:43 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_key_value(char *arg, char **key, char **value)
{
	size_t	len;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos == NULL)
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		len = equal_pos - arg;
		*key = ft_substr(arg, 0, len);
		*value = ft_substr(arg, len + 1, ft_strlen(arg) - len - 1);
	}
}

char	*ft_find_key(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}
