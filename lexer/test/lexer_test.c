#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>

void print_token_result(t_lexer *lexer)
{
    t_token_type *tok;
    
    while((tok = lexer->next_token(lexer))->type != END)
    {
        printf("token=[%s], value=[%s]\n", token_type_str(tok->type), tok->value);
        free_token(tok);
    }
    free_token(tok);
    return ;
}

int main(void)
{
    char *line;
    t_lexer *lexer;

    while(1)
    {
        line = readline("lexer> "); 
        if (line == NULL)
        {
            ft_putendl_fd("exit", STDOUT_FILENO);
            break;
        }
        lexer = new(line);
        print_token_result(lexer);
        free_lexer(lexer);
    }
    return 0;
}