#include "lexer.h"

t_token_type *handle_pipe(t_lexer *self) {
    char str[2];
    str[0] = self->ch;
    str[1] = '\0';
    return new_token(PIPE, str);
}

t_token_type *handle_quote(t_lexer *self) {
    char *ident = self->read_string(self);
    t_token_type *tok = new_token(WORD, ident);
    free(ident);
    return tok;
}

t_token_type *handle_end(t_lexer *self) {
    return new_token(END, "");
}

t_token_type *handle_word_or_single(t_lexer *self) {
    if (is_letter(self->ch)) {
        char* ident = self->read_identifier(self);
        t_token_type *tok = new_token(WORD, ident);
        free(ident);
        return tok;
    } else {
        char str_single[2];
        str_single[0] = self->ch;
        str_single[1] = '\0';
        return new_token(WORD, str_single);
    }
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
    self->read_char(self);
    return tok;
}
