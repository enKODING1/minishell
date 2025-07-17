/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_signal2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:17:25 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 19:19:40 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pipe_status_handler(int right_status, int *status)
{
	int	right_sig;

	right_sig = 0;
	if (WIFSIGNALED(right_status))
		right_sig = WTERMSIG(right_status);
	if (right_sig == SIGINT)
	{
		ft_putstr_fd("^C\n", STDERR_FILENO);
		*status = 130;
	}
	else if (right_sig == SIGQUIT)
	{
		ft_putendl_fd("^\\Quit", STDERR_FILENO);
		*status = 131;
	}
	else
	{
		if (WIFEXITED(right_status))
			*status = WEXITSTATUS(right_status);
		else if (WIFSIGNALED(right_status))
			*status = 128 + WTERMSIG(right_status);
	}
	signal(SIGINT, sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void	external_signal(int *status)
{
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
		{
			ft_putstr_fd("^C\n", STDERR_FILENO);
			*status = 130;
		}
		else if (WTERMSIG(*status) == SIGQUIT)
		{
			ft_putendl_fd("^\\Quit", STDERR_FILENO);
			*status = 131;
		}
	}
	else
	{
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			*status = 128 + WTERMSIG(*status);
	}
	signal(SIGINT, sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
