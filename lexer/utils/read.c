#include "lexer.h"

void read_char(t_lexer *self)
{
    if (self->read_position >= ft_strlen(self->input))
        self->ch = 0;
    else 
        self->ch = self->input[self->read_position];
    self->position = self->read_position;
    self->read_position += 1;
}

char peek_char(t_lexer *self)
{
    if(self->read_position >= ft_strlen(self->input))
        return 0;
    return self->input[self->read_position];
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

int is_letter(int c)
{
    if (ft_isalpha(c) || c == '_' || c == '-' || c == '.' || c == '/')
        return 1;
    return 0;
}