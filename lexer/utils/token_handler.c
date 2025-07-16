/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:14:38 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:52:35 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_type	*handle_pipe(t_lexer *self)
{
	char	str[2];

	str[0] = self->ch;
	str[1] = '\0';
	self->read_char(self);
	return (new_token(PIPE, str));
}

static int	is_available_char(char c)
{
	return (c != '\0' && c != ' ' && c != '\t' && c != '\n' && c != '|'
		&& c != '<' && c != '>');
}

t_token_type	*handle_quote(t_lexer *self)
{
	int				start;
	char			quote;
	char			*ident;
	t_token_type	*tok;

	start = self->position;
	while (is_available_char(self->ch))
	{
		if (self->ch == '\'' || self->ch == '"')
		{
			quote = self->ch;
			self->read_char(self);
			while (self->ch != quote && self->ch != '\0')
				self->read_char(self);
			if (self->ch == quote)
				self->read_char(self);
		}
		else
			self->read_char(self);
	}
	ident = ft_substr(self->input, start, self->position - start);
	tok = new_token(WORD, ident);
	free(ident);
	return (tok);
}

t_token_type	*handle_end(void)
{
	return (new_token(END, ""));
}

t_token_type	*next_token(t_lexer *self)
{
	t_token_type	*tok;

	self->skip_whitespace(self);
	if (self->ch == '|')
		tok = handle_pipe(self);
	else if (self->ch == '<')
		tok = handle_in(self);
	else if (self->ch == '>')
		tok = handle_out(self);
	else if (self->ch == '\'' || self->ch == '"')
		tok = handle_quote(self);
	else if (self->ch == '\0')
		tok = handle_end();
	else
		tok = handle_word_or_single(self);
	return (tok);
}
