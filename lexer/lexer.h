/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:12:20 by skang             #+#    #+#             */
/*   Updated: 2025/07/17 00:34:25 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "stdlib.h"
# include "token.h"
# include <stdio.h>

typedef struct s_lexer
{
	char			*input;
	int				position;
	int				read_position;
	char			ch;
	void			(*read_char)(struct s_lexer *self);
	t_token_type	*(*next_token)(struct s_lexer *self);
	char			*(*read_identifier)(struct s_lexer *self);
	char			*(*read_string)(struct s_lexer *self);
	char			*(*read_number)(struct s_lexer *self);
	char			(*peek_char)(struct s_lexer *self);
	void			(*skip_whitespace)(struct s_lexer *self);
}					t_lexer;

/* t_lexer method */
void				read_char(t_lexer *self);
t_token_type		*next_token(t_lexer *self);
char				*read_identifier(t_lexer *self);
char				*read_string(t_lexer *self);
char				*read_number(t_lexer *self);
char				peek_char(t_lexer *self);
void				skip_whitespace(t_lexer *self);

/* util functions */
const char			*token_type_str(t_token type);
t_token_type		*new_token(t_token token_type, char *ch);
t_lexer				*new(char *input);
int					is_letter(int c);
void				free_lexer(t_lexer *lexer);
void				free_token(t_token_type *tok);

t_token_type		*handle_pipe(t_lexer *self);
t_token_type		*handle_in(t_lexer *self);
t_token_type		*handle_out(t_lexer *self);
t_token_type		*handle_quote(t_lexer *self);
t_token_type		*handle_end(void);
t_token_type		*handle_word_or_single(t_lexer *self);

#endif
