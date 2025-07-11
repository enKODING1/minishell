/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:08:36 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:32:20 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	exec_exit(char **argv)
{
	int	i;
	int	exit_num;

	i = 0;
	if (ft_arglen(argv) == 0)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(0);
	}
	if (ft_arglen(argv) > 1)
	{
		exec_error_handler(STDERR_FILENO, "exit", NULL, "TOO MANY ARG");
		return ;
	}
	if (ft_check(argv[i]))
	{
		exec_error_handler(STDERR_FILENO, "exit", NULL, "INVALID ARG");
		exit(0);
	}
	exit_num = ft_atoi(argv[0]);
	exit(exit_num % 256);
}
