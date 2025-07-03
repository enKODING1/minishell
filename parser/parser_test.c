#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
//test main
int main(void)
{
    
//    char *input = "< EOF cat -e | cat -e | cat -e | cat -e | cat >> outfile";
    // char *input = "export a= 'hello world' ";
    char input[255];
    while(1)
    {
    
    printf(">> ");
    fgets(input, sizeof(input), stdin);
    if (ft_strncmp(input, "exit", 4))
    {
        t_lexer *lexer = new(input);
        t_token_node *tok_head = create_token_list(lexer);

        t_parser parser;
        parser_init(&parser, tok_head);
        print_token_list(tok_head);
        // printf("--- 파싱 시작 ---\n");
        t_node *ast_root = parse_pipe(&parser);

        if (parser.has_error)
        {
            printf("--- 문법 에러 ---\n");
            // free_ast(ast_root);
        }
        else
        {
            printf("--- 파싱 완료 ---\n\n");
            print_ast(ast_root, 0);
            // free_ast(ast_root);
        }
        free_token_list(tok_head);
        free_lexer(lexer);
    }
}
    return 0;
}