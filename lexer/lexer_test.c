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
    char *input = "ls -l | grep \".txt\"";
    t_lexer *lexer = new(input);
    t_token_type *tok; 

    while(tok->type != END)
    {
        tok = lexer->next_token(lexer);
        printf("token=[%s], value=[%s]\n", token_type_str(tok->type), tok->value);
        // printf("position: %d, read_position: %d\n\n\n", lexer->position, lexer->read_position);
    }
    return 0;
}
