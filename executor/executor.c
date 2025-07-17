/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:42:23 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:52:09 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

static void	init_shell(t_minishell *shell_info, int argc, char **argv,
		char **envp)
{
	shell_info->envp = main_init(argc, argv, envp);
	shell_info->status = 0;
	set_sig();
}

static int	process_input_line(char **line)
{
	*line = readline("minishell> ");
	if (*line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (0);
	}
	if (**line)
		add_history(*line);
	return (1);
}

static void	execute_command_line(char *line, t_minishell *shell_info)
{
	t_lexer			*lexer;
	t_token_node	*tok_head;
	t_parser		parser;
	t_node			*ast_root;

	lexer = new (line);
	tok_head = create_token_list(lexer);
	parser_init(&parser, tok_head);
	ast_root = parse_pipe(&parser);
	if (parser.has_error)
		printf("minishell: syntax error near unexpected token\n");
	execute(ast_root, shell_info);
	cleanup_resources(line, ast_root, tok_head, lexer);
}

static void	shell_loop(t_minishell *shell_info)
{
	char	*line;

	while (1)
	{
		if (!process_input_line(&line))
			break ;
		execute_command_line(line, shell_info);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell_info;

	init_shell(&shell_info, argc, argv, envp);
	shell_loop(&shell_info);
	free_envp_tmp(shell_info.envp);
	set_printf_on();
	return (0);
}
