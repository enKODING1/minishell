#include "lexer.h"

t_token_type *handle_pipe(t_lexer *self) {
    char str[2];
    str[0] = self->ch;
    str[1] = '\0';
    self->read_char(self);
    return new_token(PIPE, str);
}

t_token_type *handle_quote(t_lexer *self) {
    // 연속된 따옴표와 일반 문자를 하나의 토큰으로 합치기
    int start = self->position;
    
    while (self->ch != '\0' && self->ch != ' ' && self->ch != '\t' && 
           self->ch != '\n' && self->ch != '|' && self->ch != '<' && self->ch != '>')
    {
        if (self->ch == '\'' || self->ch == '"')
        {
            char quote = self->ch;
            self->read_char(self); // 여는 따옴표 넘김
            while (self->ch != quote && self->ch != '\0')
                self->read_char(self);
            if (self->ch == quote)
                self->read_char(self); // 닫는 따옴표 넘김
        }
        else
        {
            self->read_char(self);
        }
    }
    
    char *ident = ft_substr(self->input, start, self->position - start);
    t_token_type *tok = new_token(WORD, ident);
    free(ident);
    return tok;
}

t_token_type *handle_end(t_lexer *self) {
    return new_token(END, "");
}

t_token_type *next_token(t_lexer *self){
    t_token_type *tok;
    self->skip_whitespace(self);
    if (self->ch == '|')
        tok = handle_pipe(self);
    else if (self->ch == '<')
        tok = handle_in(self);
    else if (self->ch == '>')
        tok = handle_out(self);
    else if (self->ch == '\'' || self->ch == '"')
        tok = handle_quote(self);
    else if (self->ch == '\0')
        tok = handle_end(self);
    else 
        tok = handle_word_or_single(self);
    return tok;
}
