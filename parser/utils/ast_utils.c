/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:56:58 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 23:14:07 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_init(t_parser *parser, t_token_node *tok_head)
{
	parser->current_token = tok_head;
	parser->has_error = 0;
}

t_token_type	*peek_token(t_parser *parser)
{
	if (parser->current_token == NULL)
		return (NULL);
	return (parser->current_token->token);
}

void	consume_token(t_parser *parser)
{
	if (parser->current_token == NULL)
		return ;
	parser->current_token = parser->current_token->next;
}
