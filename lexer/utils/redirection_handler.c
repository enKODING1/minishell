/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:14:31 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:14:32 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_type	*handle_in(t_lexer *self)
{
	char	str[3];

	if (self->peek_char(self) == '<')
	{
		self->read_char(self);
		str[0] = '<';
		str[1] = '<';
		str[2] = '\0';
		self->read_char(self);
		return (new_token(HEREDOC, str));
	}
	else
	{
		str[0] = self->ch;
		str[1] = '\0';
		self->read_char(self);
		return (new_token(IN, str));
	}
}

t_token_type	*handle_out(t_lexer *self)
{
	char	str[3];

	if (self->peek_char(self) == '>')
	{
		self->read_char(self);
		str[0] = '>';
		str[1] = '>';
		str[2] = '\0';
		self->read_char(self);
		return (new_token(APPEND, str));
	}
	else
	{
		str[0] = self->ch;
		str[1] = '\0';
		self->read_char(self);
		return (new_token(OUT, str));
	}
}
