/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:00:35 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 20:02:27 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	find_message(char **argv)
{
	int	i;
	int j;

	i = 0;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	exec_echo(char **argv,char **envp_list)
{
	char **argv_list;
	int	option;
	int	i;

	argv_list = ft_argv_filter(argv, envp_list);
	i = find_message(argv_list);
	option = (i > 0);
	if (argv_list[i] == NULL)
	{
		if (option == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	while (argv_list[i])
	{
		ft_putstr_fd(argv_list[i], STDOUT_FILENO);
		if (argv_list[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
