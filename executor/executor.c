#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	t_lexer *lexer;
	t_token_node *tok_head;
	t_parser parser;
	t_node *ast_root;
	char **envp_list;
	char *line;
	int status;
	t_minishell shell_info;

	envp_list = main_init(argc,argv,envp);
	shell_info.envp = envp_list;
	shell_info.status = 0;
	set_sig();
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break;
		}
		if (*line)
			add_history(line);
		lexer = new(line);
		tok_head = create_token_list(lexer);
		parser_init(&parser, tok_head);
		ast_root = parse_pipe(&parser);
		execute(ast_root, &shell_info);
		free(line);
		free_ast(ast_root);
		free_token_list(tok_head);
		free_lexer(lexer);
	}
	free_envp_tmp(envp_list);
	set_printf_on();
	return (0);
}