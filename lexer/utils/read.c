/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:14:25 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:14:26 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	read_char(t_lexer *self)
{
	if (self->read_position >= ft_strlen(self->input))
		self->ch = 0;
	else
		self->ch = self->input[self->read_position];
	self->position = self->read_position;
	self->read_position += 1;
}

char	peek_char(t_lexer *self)
{
	if (self->read_position >= ft_strlen(self->input))
		return (0);
	return (self->input[self->read_position]);
}

char	*read_identifier(t_lexer *self)
{
	int	position;

	position = self->position;
	while (is_letter(self->ch))
	{
		self->read_char(self);
	}
	return (ft_substr(self->input, position, self->position - position));
}

char	*read_string(t_lexer *self)
{
	int		position;
	char	quote;

	quote = self->ch;
	position = self->position;
	self->read_char(self);
	while (self->ch != quote)
	{
		if (self->ch == '\0')
			break ;
		self->read_char(self);
	}
	if (self->ch == quote)
		self->read_char(self);
	return (ft_substr(self->input, position, self->position - position));
}

int	is_letter(int c)
{
	if ((c >= 33 && c <= 126) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
