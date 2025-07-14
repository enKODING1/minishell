/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 07:00:23 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/15 07:00:26 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_option_check(char *argv, int *status, char *cmd)
{
	if (argv != NULL)
	{
		if (argv[0] == '-')
		{
			*status = 1;
			exec_error_handler(STDERR_FILENO, cmd, argv, "bad option");
			return (1);
		}
	}
	return (0);
}
