/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:42:01 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 00:35:40 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>

void	cleanup_resources(char *line, t_node *ast_root, t_token_node *tok_head,
		t_lexer *lexer)
{
	free(line);
	free_ast(ast_root);
	free_token_list(tok_head);
	free_lexer(lexer);
}

void	free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**replace_cmd_args(t_cmd_node *cmd, t_minishell *shell_info)
{
	char	**old_args;
	char	**new_args;

	old_args = cmd->args;
	new_args = ft_argv_filter(cmd->args, shell_info->envp, &shell_info->status);
	if (!new_args)
		return (NULL);
	free_cmd_args(old_args);
	cmd->args = new_args;
	return (new_args);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
