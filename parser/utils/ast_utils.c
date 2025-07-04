#include "parser.h"

void parser_init(t_parser *parser, t_token_node *tok_head)
{
    parser->current_token = tok_head;
    parser->has_error = 0;
}

t_token_type * peek_token(t_parser *parser)
{
    if (parser->current_token == NULL)
        return NULL;
    return parser->current_token->token;
}

void consume_token(t_parser *parser)
{
    if (parser->current_token == NULL)
        return;
    parser->current_token = parser->current_token->next;
}

void free_token_list(t_token_node *head)
{
    if (!head)
        return ;
    t_token_node *ptr;
    ptr = head;

    while(ptr)
    {
        head = ptr->next;    
        free_token(ptr->token);
        free(ptr);
        ptr = head;
    }
}