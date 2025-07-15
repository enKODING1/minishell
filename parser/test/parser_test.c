#include "parser.h"

static int get_input(char *input, size_t size) {
    printf(">> ");
    return fgets(input, size, stdin) != NULL;
}

static void handle_parse_error(void) {
    printf("--- 문법 에러 ---\n");
}

static void parse_and_print(char *input) {
    t_lexer *lexer = new(input);
    t_token_node *tok_head = create_token_list(lexer);
    t_parser parser;
    parser_init(&parser, tok_head);
    print_token_list(tok_head);
    t_node *ast_root = parse_pipe(&parser);
    if (parser.has_error) {
        handle_parse_error();
        free_ast(ast_root);
    } else {
        printf("--- 파싱 완료 ---\n\n");
        print_ast(ast_root, 0);
        free_ast(ast_root);
    }
    free_token_list(tok_head);
    free_lexer(lexer);
}

int main(void)
{
    char input[255];
    while(1)
    {
        if (!get_input(input, sizeof(input)))
            break;
        if (ft_strncmp(input, "exit", 4))
            parse_and_print(input);
    }
    return 0;
}