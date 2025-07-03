
#include "executor.h"

char **main_init(int argc, char **argv, char **envp)
{
    if(argc != 2)
        (void) argc;
    (void) argv;
    print_edge_shell_banner_with_style();
    return (init_envp(envp));
}

int main(int argc, char **argv, char **envp)
{
    t_lexer *lexer;
    t_token_node *tok_head;
    t_parser parser;
    t_node *ast_root;    
    char **envp_list;
    char *line;
    int is_parser_error;

    envp_list = main_init(argc,argv,envp);
    set_sig();
    // set_printf_off();
    while (1)
    {
        is_parser_error = 0;
        line = readline("edgeshell> ");
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
        execute(ast_root, envp_list);
        free(line);
        free_token_list(tok_head);
        free_lexer(lexer);
    }
    free_envp_tmp(envp_list);
    return (0);
}