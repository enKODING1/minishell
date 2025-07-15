#include "lexer.h"

t_token_type *handle_in(t_lexer *self) {
    char str[3];
    if(self->peek_char(self) == '<') {
        self->read_char(self);
        str[0] = '<';
        str[1] = '<';
        str[2] = '\0';
        return new_token(HEREDOC, str);
    } else {
        str[0] = self->ch;
        str[1] = '\0';
        return new_token(IN, str);
    }
}

t_token_type *handle_out(t_lexer *self) {
    char str[3];
    if(self->peek_char(self) == '>') {
        self->read_char(self);
        str[0] = '>';
        str[1] = '>';
        str[2] = '\0';
        return new_token(APPEND, str);
    } else {
        str[0] = self->ch;
        str[1] = '\0';
        return new_token(OUT, str);
    }
} 