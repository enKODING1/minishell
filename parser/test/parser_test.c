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

static int	get_input(char *input, size_t size)
{
	printf(">> ");
	return (fgets(input, size, stdin) != NULL);
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
		free_ast(ast_root);
	}
	else
	{
		printf("--- 파싱 완료 ---\n\n");
		print_ast(ast_root, 0);
		free_ast(ast_root);
	}
	free_token_list(tok_head);
	free_lexer(lexer);
}

int	main(void)
{
	char	input[255];

	while (1)
	{
		if (!get_input(input, sizeof(input)))
			break ;
		if (ft_strncmp(input, "exit", 4))
			parse_and_print(input);
	}
	return (0);
}
