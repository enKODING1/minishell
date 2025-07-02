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

	i = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
		i++;
	return (i);
}

void	exec_echo(int *fd, char **argv)
{
	int	option;
	int	i;

	i = find_message(argv);
	option = (i > 1);
	if (argv[i] == NULL)
	{
		if (option == 0)
			ft_putstr_fd("\n", fd[1]);
		return ;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd[1]);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd[1]);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", fd[1]);
}
