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
    // char *input = "ls -l | grep .txt";
    // char *input = "ls -l";
    char *input = "cat < input.txt";
    t_lexer *lexer = new(input);
    t_token_type *tok; 

    int i = 0;
    while(i < 3)
    {
        tok = lexer->next_token(lexer);
        printf("token=[%s], value=[%s]\n", token_type_str(tok->type), tok->value);
        // printf("position: %d, read_position: %d\n\n\n", lexer->position, lexer->read_position);
        i++;
    }
    return 0;
}
