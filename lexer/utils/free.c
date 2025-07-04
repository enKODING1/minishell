/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:48:41 by skang             #+#    #+#             */
/*   Updated: 2025/07/04 19:58:42 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void free_lexer(t_lexer *lexer)
{
    if (!lexer)
        return ;
    if (lexer->input)
        free(lexer->input);
    free(lexer);
}

void free_token(t_token_type *tok)
{
    if (!tok)
        return ;
    if (tok->value)
        free(tok->value);
    free(tok);
}