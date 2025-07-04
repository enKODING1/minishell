#include "lexer.h"

t_lexer *new(char *input)
{
    t_lexer *lexer = (t_lexer *)ft_calloc(sizeof(t_lexer),1);
    lexer->input = ft_strdup(input);
    lexer->read_char = read_char;
    lexer->next_token = next_token;
    lexer->read_identifier = read_identifier;
    lexer->read_string = read_string;
    lexer->peek_char = peek_char;
    lexer->skip_whitespace = skip_whitespace;
    lexer->read_char(lexer);
    return lexer;
}

t_token_type *new_token(t_token token_type, char *ch)
{
    t_token_type * tok = (t_token_type *)malloc(sizeof(t_token_type));    
    if (!tok)
        return NULL; 
    /*token_type, ch 별도의 메모리 공간에 할당하기 ft_strdup */
    tok->type = token_type;
    tok->value = ft_strdup(ch);
    return tok;
}

