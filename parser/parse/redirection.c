#include "parser.h"

t_redir *parse_redirs(t_parser *parser)
{
    t_redir *redir_head = (t_redir *)ft_calloc(1, sizeof(t_redir));

    redir_head->type = peek_token(parser)->type;
    consume_token(parser);

    if (!peek_token(parser) || peek_token(parser)->type != WORD)
    {
        parser->has_error = 1;
        free(redir_head);
        return NULL; 
    }

    redir_head->filename = ft_strdup(peek_token(parser)->value);
    consume_token(parser);
    return redir_head;
}