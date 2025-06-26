#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

// t_redirs *parse_redirs(t_lexer *lexer)
// {
    
// }

// t_node *parse_cmd(t_lexer *lexer)
// {

// }

// t_node *parse_pipe(t_lexer *lexer)
// {
//     t_token_type *tok;

//     // if(lexer->)
// }

//test main
int main(void)
{
    
    char *input = "< file cat | cat > outfile";
    t_lexer *lexer = new(input);
    t_token_node *tok_head = create_token_list(lexer);
    print_token_list(tok_head);

    // t_node *ast_root = (t_node *)malloc(sizeof(t_node));
    // if (!ast_root)
    //     return 0;
    // t_lexer *lexer = new(input);   

    // ast_root = parse_pipe(lexer);

    // t_token_type *tok;

    // while(tok->type != END)
    // {
    //     tok = lexer->next_token(lexer);
    //     printf("type[%s], value[%s]\n", token_type_str(tok->type), tok->value);
    // }

    return 0;
}