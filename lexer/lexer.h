#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "stdlib.h"

typedef struct s_lexer{
    char * input; // 입력
    int position; // 현재 위치
    int read_position; // 읽을 위치
    char ch; // 현재 문자 
    void (*read_char)(struct s_lexer *self);
    t_token_type *(*next_token)(struct s_lexer *self);
    char *(*read_identifier)(struct s_lexer * self);
    char *(* read_number)(struct s_lexer * self);
    char (*peek_char)(struct s_lexer *self);
    void (* skip_whitespace)(struct s_lexer *self);
} t_lexer;

/* t_lexer method */
void read_char(t_lexer *self);
t_token_type *next_token(t_lexer *self);
char * read_identifier(t_lexer *self);
char * read_number(t_lexer *self);
char peek_char(t_lexer *self);
void skip_whitespace(t_lexer *self);

/* util functions */
const char * token_type_str(t_token type);
t_token_type *new_token(t_token token_type, char *ch);
t_lexer *new(char *input);

#endif