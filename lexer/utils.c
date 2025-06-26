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
    lexer->read_string = read_string;
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
    char str[3];

    self->skip_whitespace(self);
    if (self->ch == '|')
    {
        str[0] = self->ch;
        str[1] = '\0';
        tok = new_token(PIPE, str);
    }
    else if (self->ch == '<')
    {
        if(self->peek_char(self) == '<')
        {
            self->read_char(self);
            str[0] = '<';
            str[1] = '<';
            str[2] = '\0';
            tok = new_token(HEREDOC, str);
        }
        else
        {
            str[0] = self->ch;
            str[1] = '\0';
            tok = new_token(IN, str);
        }
    }
    else if (self->ch == '>')
    {
        if(self->peek_char(self) == '>')
        {
            self->read_char(self);
            str[0] = '>';
            str[1] = '>';
            str[2] = '\0';
            tok = new_token(APPEND, str);
        }
        else
        {
            str[0] = self->ch;
            str[1] = '\0';
            tok = new_token(OUT, str);
        }
    }
    else if (self->ch == '\'' || self->ch == '"')
    {
        char *ident = self->read_string(self);
        tok = new_token(WORD, ident);
        free(ident);
    }
    else if (self->ch == '\0')
        tok = new_token(END, "");
    else 
    {
        if (is_letter(self->ch))
        {
            char* ident = self->read_identifier(self);
            tok = new_token(WORD, ident);
            free(ident);
            return (tok);
        }
        else
        {
            char str_single[2];
            str_single[0] = self->ch;
            str_single[1] = '\0';
            tok = new_token(WORD, str_single);
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
    int position;

    position = self->position;
    while(is_letter(self->ch))
    {
        self->read_char(self);
    }

    return ft_substr(self->input, position, self->position - position);
}

char * read_string(t_lexer *self)
{
    int position;
    char quote;

    quote = self->ch;
    self->read_char(self);
    position = self->position;
    while(self->ch != quote)
    {
        if (self->ch == '\0')
        {
            // 닫히지 않은 따옴표 처리
            break;
        }
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

void free_lexer(t_lexer *lexer)
{
    if (!lexer)
        return ;
    if (lexer->input)
        free(lexer->input);
    free(lexer);
}

void free_token(t_token_type *tok)
{
    if (!tok)
        return ;
    if (tok->value)
        free(tok->value);
    free(tok);
}