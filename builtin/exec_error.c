/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:04:57 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 20:07:58 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_error_handler(int fd,
		char *command,
		char *target,
		char *error_message)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(command, fd);
	ft_putstr_fd(" : ", fd);
	ft_putstr_fd(error_message, fd);
	if (target)
	{
		ft_putstr_fd(" : ", fd);
		ft_putstr_fd(target, fd);
	}
	ft_putstr_fd("\n", fd);
}
