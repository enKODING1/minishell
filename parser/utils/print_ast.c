/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:57:04 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 23:23:02 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_cmd(t_cmd_node *cmd_node, int *indent)
{
	t_redir	*r;
	int		i;
	int		j;

	i = 0;
	if (cmd_node->cmd)
		printf("CMD: [%s]\n", cmd_node->cmd);
	else
		printf("CMD: [%s]\n", "NULL");
	while (cmd_node->args[i])
	{
		j = -1;
		while (++j < *indent + 1)
			printf("  ");
		printf("ARG: %s\n", cmd_node->args[i++]);
	}
	r = cmd_node->redirs;
	while (r)
	{
		j = -1;
		while (++j < *indent + 1)
			printf("  ");
		printf("REDIR: %s %s\n", token_type_str(r->type), r->filename);
		r = r->next;
	}
}

void	print_ast(t_node *node, int indent)
{
	t_pipe_node	*pipe_node;
	t_cmd_node	*cmd_node;
	int			i;

	if (!node)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (node->type == NODE_PIPE)
	{
		pipe_node = (t_pipe_node *)node;
		printf("PIPE\n");
		print_ast(pipe_node->left, indent + 1);
		print_ast(pipe_node->right, indent + 1);
	}
	else if (node->type == NODE_CMD)
	{
		cmd_node = (t_cmd_node *)node;
		print_cmd(cmd_node, &indent);
	}
}
