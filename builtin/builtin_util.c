/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:39:29 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 21:32:22 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_arglen(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

char	**get_envp_list(char **envp_list)
{
	char	**tmp_list;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp_list = malloc(sizeof(char *) * (ft_arglen(envp_list) + 1));
	if (!envp_list)
		return (NULL);
	while (envp_list[i])
	{
		tmp_list[i] = ft_strdup(envp_list[i]);
		i++;
	}
	tmp_list[i] = NULL;
	return (tmp_list);
}

void	free_envp(char **envp_list)
{
	int	i;

	i = 0;
	while (envp_list && envp_list[i])
	{
		free(envp_list[i]);
		i++;
	}
	free(envp_list);
}

char	*search_envp(char *target, char **envp_list)
{
	size_t	len;
	int		i;

	if (!target || !envp_list)
		return (NULL);
	i = 0;
	len = ft_strlen(target);
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], target, len) == 0
			&& envp_list[i][len] == '=')
			return (envp_list[i] + len + 1);
		i++;
	}
	return (NULL);
}
