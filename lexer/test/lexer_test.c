/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:13:17 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:18:26 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <readline/history.h>
#include <readline/readline.h>

void	print_token_result(t_lexer *lexer)
{
	t_token_type	*tok;

	tok = lexer->next_token(lexer);
	while (tok->type != END)
	{
		printf("token=[%s], value=[%s]\n", token_type_str(tok->type),
			tok->value);
		free_token(tok);
		tok = lexer->next_token(lexer);
	}
	free_token(tok);
	return ;
}

int	main(void)
{
	char	*line;
	t_lexer	*lexer;

	while (1)
	{
		line = readline("lexer> ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		lexer = new (line);
		print_token_result(lexer);
		free_lexer(lexer);
	}
	return (0);
}
