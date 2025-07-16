/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:08:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:08:55 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*parse_redirs(t_parser *parser)
{
	t_redir	*redir_head;

	redir_head = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir_head->type = peek_token(parser)->type;
	consume_token(parser);
	if (!peek_token(parser) || peek_token(parser)->type != WORD)
	{
		parser->has_error = 1;
		free(redir_head);
		return (NULL);
	}
	redir_head->filename = ft_strdup(peek_token(parser)->value);
	consume_token(parser);
	return (redir_head);
}
