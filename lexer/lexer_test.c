#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

// void test_next_token()
// {
//     char *input = "cat < input.txt";
   
    
// }

int main(void)
{
    // char *input = "ls -l | grep .txt < << > >> ./../blog cat -e";
    // char *input = "ls -l";
    // char *input = "cat < input.txt";
    char *input = "ls -l | grep \".txt\" *";
    t_lexer *lexer = new(input);
    t_token_type *tok; 

    while((tok = lexer->next_token(lexer))->type != END)
    {
        printf("token=[%s], value=[%s]\n", token_type_str(tok->type), tok->value);
        free_token(tok);
    }
    free_token(tok); 
    free_lexer(lexer);
    return 0;
}
