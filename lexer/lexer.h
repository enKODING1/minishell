#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct s_lexer{
    char * input; // 입력
    int position; // 현재 위치
    int read_position; // 읽을 위치
    char ch; // 현재 문자 
    void (*read_char)(t_lexer *self);
    t_token_type (*next_token)(t_lexer *self);
    char *(*read_identifier)(t_lexer * self);
    char *(* read_number)(t_lexer self);
    char (*peek_char)(t_lexer *self);
    void (* skip_whitespace)(t_lexer *self);
} t_lexer;

void read_char(t_lexer *self);
t_token_type next_token(t_lexer *self);
char * read_identifier(t_lexer *self);
char * read_number(t_lexer *self);
char peek_char(t_lexer *self);
void *skip_whitespcae(t_lexer *self);

#endif