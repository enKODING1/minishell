/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:12:05 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:16:21 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*new(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)ft_calloc(sizeof(t_lexer), 1);
	lexer->input = ft_strdup(input);
	lexer->read_char = read_char;
	lexer->next_token = next_token;
	lexer->read_identifier = read_identifier;
	lexer->read_string = read_string;
	lexer->peek_char = peek_char;
	lexer->skip_whitespace = skip_whitespace;
	lexer->read_char(lexer);
	return (lexer);
}

t_token_type	*new_token(t_token token_type, char *ch)
{
	t_token_type	*tok;

	tok = (t_token_type *)malloc(sizeof(t_token_type));
	if (!tok)
		return (NULL);
	tok->type = token_type;
	tok->value = ft_strdup(ch);
	if (!tok->value)
	{
		free(tok);
		tok = NULL;
		return (NULL);
	}
	return (tok);
}
