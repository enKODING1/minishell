#include "lexer.h"

static void process_quote_token(t_lexer *self)
{
	char	quote;

	quote = self->ch;
	self->read_char(self);
	while (self->ch != quote && self->ch != '\0')
		self->read_char(self);
	if (self->ch == quote)
		self->read_char(self);
}

static void process_equal_quote_token(t_lexer *self)
{
	char	quote;

	self->read_char(self);
	quote = self->ch;
	self->read_char(self);
	while (self->ch != quote && self->ch != '\0')
		self->read_char(self);
	if (self->ch == quote)
		self->read_char(self);
}

static t_token_type *handle_identifier_token(t_lexer *self)
{
	int		start;
	char	*ident;
	t_token_type *tok;

	start = self->position;
	while (self->ch != '\0' && self->ch != ' ' && self->ch != '\t' && 
		   self->ch != '\n' && self->ch != '|' && self->ch != '<' && self->ch != '>')
	{
		if (self->ch == '\'' || self->ch == '"')
			process_quote_token(self);
		else if (self->ch == '=' && (self->peek_char(self) == '\'' || self->peek_char(self) == '"'))
			process_equal_quote_token(self);
		else
			self->read_char(self);
	}
	ident = ft_substr(self->input, start, self->position - start);
	tok = new_token(WORD, ident);
	free(ident);
	return (tok);
}

t_token_type *handle_word_or_single(t_lexer *self) {
	char	str_single[2];

	if (is_letter(self->ch)) {
		return handle_identifier_token(self);
	} else {
		str_single[0] = self->ch;
		str_single[1] = '\0';
		self->read_char(self);
		return new_token(WORD, str_single);
	}
} 