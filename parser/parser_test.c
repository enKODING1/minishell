#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

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

    redir_head->filename = peek_token(parser)->value;
    consume_token(parser);
    return redir_head;
}

t_node *parse_cmd(t_parser *parser)
{
    t_cmd_node *cmd_head = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
    cmd_head->type = NODE_CMD;
    cmd_head->args = (char **)ft_calloc(20, sizeof(char *));

    int i = 0;
    while (peek_token(parser) && peek_token(parser)->type != PIPE && peek_token(parser)->type != END)
    {
        if (peek_token(parser)->type == WORD)
        {
           if (cmd_head->cmd == NULL) 
                cmd_head->cmd = peek_token(parser)->value;
			else 
                cmd_head->args[i++] = peek_token(parser)->value;
			consume_token(parser);
        }
        else if (peek_token(parser)->type >= HEREDOC && peek_token(parser)->type <= IN)
        {
            t_redir *redir = parse_redirs(parser);
            if (parser->has_error)
                return NULL;
            if (!cmd_head->redirs)
            {
                cmd_head->redirs = redir;
            }
            else
            {
                t_redir *current = cmd_head->redirs;
                while(current->next)
                    current = current->next;
                current->next = redir;
            }
        }
        else break;
    }
    return (t_node *)cmd_head;
}

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

void print_ast(t_node *node, int indent)
{
	if (!node) return;
	for (int i = 0; i < indent; i++) printf("  ");

	if (node->type == NODE_PIPE)
	{
		t_pipe_node *pipe_node = (t_pipe_node *)node;
		printf("PIPE\n");
		print_ast(pipe_node->left, indent + 1);
		print_ast(pipe_node->right, indent + 1);
	}
	else if (node->type == NODE_CMD)
	{
		t_cmd_node *cmd_node = (t_cmd_node *)node;
		printf("CMD: [%s]\n", cmd_node->cmd ? cmd_node->cmd : "NULL");
		
		for (int i = 0; cmd_node->args[i]; i++)
		{
			for (int j = 0; j < indent + 1; j++) printf("  ");
			printf("ARG: %s\n", cmd_node->args[i]);
		}
		
		t_redir *r = cmd_node->redirs;
		while(r)
		{
			for (int j = 0; j < indent + 1; j++) printf("  ");
			printf("REDIR: %s %s\n", token_type_str(r->type), r->filename);
			r = r->next;
		}
	}
}

//test main
int main(void)
{
    
   char *input = "< EOF cat -e | cat -e | cat -e | cat -e | cat >> outfile";
	
	t_lexer *lexer = new(input);
	t_token_node *tok_head = create_token_list(lexer);

	t_parser parser;
	parser_init(&parser, tok_head);
    print_token_list(tok_head);
	printf("--- 파싱 시작 ---\n");
	t_node *ast_root = parse_pipe(&parser);

	if (parser.has_error)
	{
		printf("--- 문법 에러 ---\n");
		// free_ast(ast_root);
	}
	else
	{
		printf("--- 파싱 완료 ---\n\n");
		print_ast(ast_root, 0);
		// free_ast(ast_root);

	}
	
	// free_token_list(tok_head);
	free(lexer->input);
	free(lexer);

    return 0;
}