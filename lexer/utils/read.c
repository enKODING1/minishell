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

char *read_string(t_lexer *self)
{
	int		start_pos;
	char	quote_type;

	quote_type = self->ch;
	start_pos = self->position; // 여는 따옴표 위치에서 시작
	read_char(self); // 여는 따옴표 소비
	while (self->ch != quote_type && self->ch != '\0')
		read_char(self);
	if (self->ch == quote_type)
		read_char(self); // 닫는 따옴표 소비
	return (ft_substr(self->input, start_pos, self->position - start_pos));
}

int is_letter(int c)
{
    if ((c >= 33 && c <= 126) || (c >= 9 && c <= 13))
        return 1;
    return 0;
}