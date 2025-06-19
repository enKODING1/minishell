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
    if (type == ILLEGAL)
        return "ILLEGAL";
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
    lexer->peek_char = peek_char;
    lexer->skip_whitespace = skip_whitespace;

    lexer->read_char(lexer);
    // printf("input:%s\n", lexer->input);
    return lexer;
}

char peek_char(t_lexer *self)
{
    if(self->read_position >= ft_strlen(self->input))
        return 0;
    return self->input[self->read_position];
}

t_token_type *next_token(t_lexer *self){
    t_token_type *tok;
    self->skip_whitespace(self);
    // ", ' 도 처리하기
    if (self->ch == '|')
        tok = new_token(PIPE, &self->ch);
    else if (self->ch == '<')
    {
        if(self->peek_char(self) == '<')
        {
            char prev_ch = self->ch;
            char *str;
            self->read_char(self);

            str = (char *)malloc(sizeof(char) * 3); // [<, <, \0]

            if(!str)
                return NULL;
            str[0] = prev_ch;
            str[1] = self->ch;
            str[2] = '\0';

            tok = new_token(HEREDOC, str);
            free(str);
        }else
        {
            tok = new_token(IN, &self->ch);
        }
    }
    else if (self->ch == '>')
    {
        if(self->peek_char(self) == '>')
        {
            char prev_ch = self->ch;
            char *str;
            self->read_char(self);
            str = (char *)malloc(sizeof(char) * 3); // [>, >, \0]
            if(!str)
                return NULL;
            str[0] = prev_ch;
            str[1] = self->ch;
            str[2] = '\0';

            tok = new_token(APPEND, str);
            free(str);
        }else
        {
            tok = new_token(OUT, &self->ch);
        }
    }
    else if (self->ch == '\0')
        tok = new_token(END, "");
    // else if (ft_isalpha(self->ch) || self->ch == '.' || self->ch == '-' || self->ch == '_')
    else 
    {
        tok = (t_token_type *)malloc(sizeof(t_token_type));
        if(is_letter(self->ch))
        {
         tok->value = self->read_identifier(self);
         /* 
            모든 문자열은 word토큰으로 취급할 거기 때문에 
            별도의 lookupident로 위 identifier에 맞는 토큰을 찾을 필요 없이
            word 토큰으로 취급해도 되지 않을까 ?
         */
         tok->type = WORD;
        }
    }
    self->read_char(self);
    return tok;
}

int is_letter(int c)
{
    if (ft_isalpha(c) || c == '_' || c == '-' || c == '.' || c == '/')
        return 1;
    return 0;
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
    while(is_letter(self->ch))
    {
        self->read_char(self);
    }

    return ft_substr(self->input, position, self->position - position);
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
