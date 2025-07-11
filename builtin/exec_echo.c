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

	i = 0;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
		i++;
	return (i);
}

void	exec_echo(char **argv)
{
	int	option;
	int	i;

	i = find_message(argv);
	option = (i > 0);
	if (argv[i] == NULL)
	{
		if (option == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
