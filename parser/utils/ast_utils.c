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

// 리다이렉션 구조체 해제 함수
void free_redir_list(t_redir *redir)
{
    t_redir *current;
    t_redir *next;
    
    if (!redir)
        return;
    
    current = redir;
    while (current)
    {
        next = current->next;
        // filename은 토큰에서 관리하므로 해제하지 않음
        free(current);
        current = next;
    }
}

// cmd_node 해제 함수
void free_cmd_node(t_cmd_node *cmd_node)
{
    int i;
    
    if (!cmd_node)
        return;
    
    // cmd와 args의 각 원소는 토큰에서 관리하므로 해제하지 않음
    if (cmd_node->args)
        free(cmd_node->args);
    
    if (cmd_node->redirs)
        free_redir_list(cmd_node->redirs);
    
    free(cmd_node);
}

// pipe_node 해제 함수
void free_pipe_node(t_pipe_node *pipe_node)
{
    if (!pipe_node)
        return;
    
    if (pipe_node->left)
        free_ast(pipe_node->left);
    if (pipe_node->right)
        free_ast(pipe_node->right);
    
    free(pipe_node);
}

// AST 전체 해제 함수
void free_ast(t_node *node)
{
    if (!node)
        return;
    
    if (node->type == NODE_PIPE)
        free_pipe_node((t_pipe_node *)node);
    else if (node->type == NODE_CMD)
        free_cmd_node((t_cmd_node *)node);
}