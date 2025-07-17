/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_children.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:31:01 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 18:07:28 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	execute_pipe_left_child(t_pipe_node *pipe_node, t_minishell *shell_info,
		int *pipefd)
{
	t_cmd_node	*cmd;

	set_signal_dfl();
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (pipe_node->left->type == NODE_PIPE)
		execute_pipe((t_pipe_node *)pipe_node->left, shell_info);
	else if (pipe_node->left->type == NODE_CMD)
	{
		cmd = (t_cmd_node *)pipe_node->left;
		if (!cmd && !cmd->cmd)
			exit(0);
		if (!replace_cmd_args(cmd, shell_info))
			exit(1);
		if (cmd->cmd && is_builtint(cmd))
		{
			redirection_handler(cmd, shell_info);
			builtin_handler(cmd, &shell_info->envp, &shell_info->status);
			exit(0);
		}
		else
			execute_pipe_command((t_cmd_node *)pipe_node->left, shell_info);
	}
	exit(0);
}

void	execute_pipe_right_child(t_pipe_node *pipe_node,
		t_minishell *shell_info, int *pipefd)
{
	t_cmd_node	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (pipe_node->right->type == NODE_PIPE)
		execute_pipe((t_pipe_node *)pipe_node->right, shell_info);
	else if (pipe_node->right->type == NODE_CMD)
	{
		cmd = (t_cmd_node *)pipe_node->right;
		if (!replace_cmd_args(cmd, shell_info))
			exit(1);
		if (cmd->cmd && is_builtint(cmd))
		{
			redirection_handler(cmd, shell_info);
			builtin_handler(cmd, &shell_info->envp, &shell_info->status);
			exit(0);
		}
		else
			execute_pipe_command((t_cmd_node *)pipe_node->right, shell_info);
	}
	exit(0);
}
