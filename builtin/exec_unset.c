/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:20:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/15 06:13:08 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_check(char *str)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_pull(int i, char **envp_list)
{
	free(envp_list[i]);
	while (envp_list[i + 1])
	{
		envp_list[i] = envp_list[i + 1];
		i++;
	}
	envp_list[i] = NULL;
}

void	exec_unset(char **argv, char ***envp_list, int *status)
{
	size_t	key_len;
	size_t	i;
	size_t	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (!ft_check(argv[i]))
			continue ;
		key_len = ft_strlen(argv[i]);
		while ((*envp_list)[j])
		{
			if (ft_strncmp(argv[i], (*envp_list)[j], key_len) == 0
				&& (*envp_list)[j][key_len] == '=')
			{
				ft_pull(j, *envp_list);
				continue ;
			}
			j++;
		}
		i++;
	}
	*status = 0;
}
