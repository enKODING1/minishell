/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:56:46 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 22:56:48 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*get_input(void)
{
	return (readline(">> "));
}

static void	handle_parse_error(void)
{
	printf("--- 문법 에러 ---\n");
}

static void	parse_and_print(char *input)
{
	t_lexer			*lexer;
	t_token_node	*tok_head;
	t_parser		parser;
	t_node			*ast_root;

	lexer = new (input);
	tok_head = create_token_list(lexer);
	parser_init(&parser, tok_head);
	print_token_list(tok_head);
	ast_root = parse_pipe(&parser);
	if (parser.has_error)
	{
		handle_parse_error();
		free_token_list(tok_head);
		free_lexer(lexer);
		return ;
	}
	printf("--- 파싱 완료 ---\n\n");
	print_ast(ast_root, 0);
	free_ast(ast_root);
	free_token_list(tok_head);
	free_lexer(lexer);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = get_input();
		if (!input)
			break ;
		if (ft_strncmp(input, "exit", 4) != 0)
		{
			add_history(input);
			parse_and_print(input);
		}
		free(input);
		if (ft_strncmp(input, "exit", 4) == 0)
			break ;
	}
	return (0);
}
