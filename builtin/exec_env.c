/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:02:45 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:29:16 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	exec_env(char **argv, char **envp_list, int *status)
{
	int	i;

	i = 0;
	if (argv[0] != NULL)
	{
		exec_error_handler(STDERR_FILENO, "env", NULL, "INVALID ARG");
		*status = 1;
		return ;
	}
	while (envp_list[i])
	{
		if (has_equal(envp_list[i]) == 1)
		{
			ft_putstr_fd(envp_list[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	*status = 0;
}
