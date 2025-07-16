/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:13:49 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 23:13:50 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_cmd(t_cmd_node *cmd_node)
{
	int	i;

	if (cmd_node->cmd)
	{
		free(cmd_node->cmd);
	}
	if (cmd_node->args)
	{
		i = 0;
		while (cmd_node->args[i])
		{
			free(cmd_node->args[i]);
			i++;
		}
		free(cmd_node->args);
		cmd_node->args = NULL;
	}
	if (cmd_node->redirs)
	{
		free_redir_list(cmd_node->redirs);
		cmd_node->redirs = NULL;
	}
	free(cmd_node);
}

static void	free_pipe(t_pipe_node *pipe_node)
{
	if (pipe_node->left)
	{
		free_ast(pipe_node->left);
		pipe_node->left = NULL;
	}
	if (pipe_node->right)
	{
		free_ast(pipe_node->right);
		pipe_node->right = NULL;
	}
	free(pipe_node);
}

void	free_ast(t_node *node)
{
	t_pipe_node	*pipe_node;
	t_cmd_node	*cmd_node;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		pipe_node = (t_pipe_node *)node;
		free_pipe(pipe_node);
	}
	else if (node->type == NODE_CMD)
	{
		cmd_node = (t_cmd_node *)node;
		free_cmd(cmd_node);
	}
}
