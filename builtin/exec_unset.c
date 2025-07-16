/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:20:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 18:34:19 by jinwpark         ###   ########.fr       */
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

void	process_unset(char **argv, char ***envp_list, size_t i, size_t j)
{
	size_t	key_len;

	while (argv[i])
	{
		j = 0;
		if (!ft_check(argv[i]))
		{
			i++;
			continue ;
		}
		key_len = ft_strlen(argv[i]);
		while ((*envp_list)[j])
		{
			if (ft_strncmp(argv[i], (*envp_list)[j], key_len) == 0
				&& ((*envp_list)[j][key_len] == '='
					|| (*envp_list)[j][key_len] == '\0'))
			{
				ft_pull(j, *envp_list);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	exec_unset(char **argv, char ***envp_list, int *status)
{
	if (ft_option_check(argv[0], status, "unset"))
		return ;
	process_unset(argv, envp_list, 0, 0);
	*status = 0;
}
