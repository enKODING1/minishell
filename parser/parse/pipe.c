/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:07:02 by skang          #+#    #+#             */
/*   Updated: 2025/07/16 23:15:23 by skang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*create_pipe_node(t_parser *parser, t_node *left_node)
{
	t_pipe_node	*pipe;

	consume_token(parser);
	if (!peek_token(parser) || peek_token(parser)->type == END)
	{
		parser->has_error = 1;
		free_ast(left_node);
		return (NULL);
	}
	pipe = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
	pipe->type = NODE_PIPE;
	pipe->left = left_node;
	pipe->right = parse_pipe(parser);
	if (parser->has_error)
	{
		free_ast(pipe->left);
		free(pipe);
		return (NULL);
	}
	return ((t_node *)pipe);
}

t_node	*parse_pipe(t_parser *parser)
{
	t_node	*node;

	if (!peek_token(parser) || peek_token(parser)->type == END)
		return (NULL);
	node = parse_cmd(parser);
	if (parser->has_error)
	{
		free_ast(node);
		return (NULL);
	}
	if (peek_token(parser) && peek_token(parser)->type == PIPE)
		return (create_pipe_node(parser, node));
	return (node);
}
