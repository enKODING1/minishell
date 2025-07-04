#include "parser.h"

t_node *parse_pipe(t_parser *parser)
{
    if (!peek_token(parser) || peek_token(parser)->type == END) 
        return NULL;

    t_node *node = parse_cmd(parser);
	if (parser->has_error) 
        return NULL;

	if (peek_token(parser) && peek_token(parser)->type == PIPE)
	{
		consume_token(parser);
		if (!peek_token(parser) || peek_token(parser)->type == END) 
        { 
            parser->has_error = 1; 
            return NULL; 
        }
		t_pipe_node *pipe = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
		pipe->type = NODE_PIPE;
		pipe->left = node;
		pipe->right = parse_pipe(parser);
		if (parser->has_error) return NULL;
		return (t_node *)pipe;
	}
	return node;
}
