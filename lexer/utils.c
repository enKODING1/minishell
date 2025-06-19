#include "lexer.h"
#include "libft.h"
#include <stdio.h>

const char * token_type_str(t_token type){
    if (type == PIPE)
        return "PIPE";
    if (type == HEREDOC)
        return "HEREDOC";
    if (type == APPEND)
        return "APPEND";
    if (type == OUT)
        return "OUT";
    if (type == IN)
        return "IN";
    if (type == WORD)
        return "WORD";
    if (type == END)
        return "END";
    return NULL;
}

t_lexer *new(char *input)
{
    t_lexer *lexer = (t_lexer *)malloc(sizeof(t_lexer));
    lexer->input = ft_strdup(input);
    lexer->read_char = read_char;
    lexer->next_token = next_token;
    lexer->read_identifier = read_identifier;
    // lexer->read_number = read_number;
    // lexer->peek_char = peek_char;
    lexer->skip_whitespace = skip_whitespace;

    lexer->read_char(lexer);
    // printf("input:%s\n", lexer->input);
    return lexer;
}

t_token_type *next_token(t_lexer *self){
    t_token_type *tok;
    self->skip_whitespace(self);
    if (self->ch == '|')
        tok = new_token(PIPE, &self->ch);
    else if (self->ch == '<')
        tok = new_token(IN, &self->ch);
    else if (self->ch == '>')
        tok = new_token(OUT, &self->ch);
    else if (self->ch == '\0')
        tok = new_token(END, NULL);
    else if (ft_isalpha(self->ch))
    {
        tok = (t_token_type *)malloc(sizeof(t_token_type));
        if(ft_isalpha(self->ch))
        {
         tok->value = self->read_identifier(self);
         tok->type = WORD;
        }
    }
    self->read_char(self);
    return tok;
}

void read_char(t_lexer *self)
{
    if (self->read_position >= ft_strlen(self->input))
        self->ch = 0;
    else 
        self->ch = self->input[self->read_position];
    self->position = self->read_position;
    self->read_position += 1;
}

char * read_identifier(t_lexer *self)
{
    int position = self->position;
    while(ft_isalpha(self->ch) || self->ch == '.' || self->ch == '-')
    {
        self->read_char(self);
    }

    return ft_substr(self->input, position, self->position);
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

void skip_whitespace(t_lexer *self)
{
    while(self->ch == ' ' || self->ch == '\t' || self->ch == '\n' || self->ch == '\r')
    {
        self->read_char(self);
    }
}
