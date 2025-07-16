/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:20:51 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 00:35:53 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	external_command(t_cmd_node *cmd_node, t_minishell *shell_info)
{
	int		pid;
	char	*cmd;

	pid = fork();
	if (pid == -1)
		printf("error run: %s\n", cmd_node->cmd);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cmd = get_cmd_path(cmd_node->cmd, shell_info->envp);
		if (cmd_node->cmd != NULL && cmd == NULL)
		{
			printf("not found command\n");
			shell_info->status = NOT_FOUND_CMD;
			exit(NOT_FOUND_CMD);
		}
		redirection_handler(cmd_node, shell_info);
		if (cmd_node->cmd)
			run_command(cmd_node, cmd, shell_info->envp);
		free(cmd);
		exit(0);
	}
	waitpid(pid, &shell_info->status, 0);
	external_signal(&shell_info->status);
}

void	execute_pipe_command(t_cmd_node *cmd_node, t_minishell *shell_info)
{
	char	*cmd;

	cmd = get_cmd_path(cmd_node->cmd, shell_info->envp);
	if (cmd_node->cmd != NULL && cmd == NULL)
	{
		printf("not found command\n");
		shell_info->status = NOT_FOUND_CMD;
		exit(NOT_FOUND_CMD);
	}
	redirection_handler(cmd_node, shell_info);
	if (cmd_node->cmd)
		run_command(cmd_node, cmd, shell_info->envp);
	free(cmd);
}
