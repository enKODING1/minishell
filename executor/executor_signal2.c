/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_signal2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:17:25 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/15 22:48:37 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pipe_signal(int left_status, int right_status, int *status)
{
	if ((left_status & 0x7F) == SIGINT)
	{
		ft_putstr_fd("^C\n", STDERR_FILENO);
		*status = left_status;
		return ;
	}
	else if ((left_status & 0x7F) == SIGQUIT)
	{
		ft_putendl_fd("^\\Quit", STDERR_FILENO);
		*status = left_status;
		return ;
	}
	if ((right_status & 0x7F) == SIGINT)
	{
		ft_putstr_fd("^C\n", STDERR_FILENO);
		*status = right_status;
	}
	else if ((right_status & 0x7F) == SIGQUIT)
	{
		ft_putendl_fd("^\\Quit", STDERR_FILENO);
		*status = right_status;
	}
	signal(SIGINT, sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void external_signal(int *status)
{
    if((*status & 0x7F) == SIGINT)
        ft_putstr_fd("^C\n", STDERR_FILENO);
    else if((*status & 0x7F) == SIGQUIT)
        ft_putendl_fd("^\\Quit", STDERR_FILENO);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, SIG_IGN);      
}
