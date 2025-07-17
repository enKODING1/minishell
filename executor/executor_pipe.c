/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:19:55 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:52:19 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	run_cmd_node(t_cmd_node *cmd, t_minishell *shell_info)
{
	int	stdout_fd;
	int	stdin_fd;

	if (!replace_cmd_args(cmd, shell_info))
	{
		shell_info->status = 1;
		return ;
	}
	if (cmd->cmd && is_builtint((t_cmd_node *)cmd))
	{
		stdout_fd = dup(STDOUT_FILENO);
		stdin_fd = dup(STDIN_FILENO);
		redirection_handler(cmd, shell_info);
		builtin_handler(cmd, &shell_info->envp, &shell_info->status);
		dup2(stdout_fd, STDOUT_FILENO);
		dup2(stdin_fd, STDIN_FILENO);
		close(stdout_fd);
		close(stdin_fd);
		signal(SIGINT, sig_c);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	external_command(cmd, shell_info);
}

void	execute(t_node *node, t_minishell *shell_info)
{
	t_cmd_node	*cmd;

	if (!node)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (node->type == NODE_PIPE)
	{
		execute_pipe((t_pipe_node *)node, shell_info);
		return ;
	}
	else if (node->type == NODE_CMD)
	{
		cmd = (t_cmd_node *)node;
		run_cmd_node(cmd, shell_info);
	}
}
