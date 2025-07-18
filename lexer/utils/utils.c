/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:14:48 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:14:50 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

const char	*token_type_str(t_token type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == OUT)
		return ("OUT");
	if (type == IN)
		return ("IN");
	if (type == WORD)
		return ("WORD");
	if (type == END)
		return ("END");
	return (NULL);
}

void	skip_whitespace(t_lexer *self)
{
	while (self->ch == ' ' || self->ch == '\t' || self->ch == '\n'
		|| self->ch == '\r')
	{
		self->read_char(self);
	}
}
