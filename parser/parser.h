#ifndef PARSER_H
#define PARSER_H

#include "libft.h"
#include "lexer.h"

typedef struct s_token_node{
    t_token_type *token;
    struct s_token_node *next;
}t_token_node;

typedef enum s_node_type{
    PIPE_NODE,
    CMD_NODE,
    REDIRS_NODE
} t_node_type;

// 범용 타입
typedef struct s_node{
    t_node_type node;
}t_node;

typedef struct s_redirs{
    t_token_type type;
    char *file; 
    struct s_redirs *redirs;
} t_redirs;

typedef struct s_pipe_node{

} t_pipe_node;

typedef struct s_cmd_node{
    t_node_type node_type;
    t_token_type type;
    char **args;
    t_redirs *redirs;
} t_cmd_node;

t_node *parse_pipe(t_lexer *lexer);
t_node *parse_cmd(t_lexer *lexer);
t_redirs *parse_redirs(t_lexer *lexer);

/* token list */
t_token_node *create_token_list(t_lexer *lexer);
t_token_node *create_token_node(t_token_type *tok);
int add_token_node(t_token_node **head, t_token_node *tok);
void print_token_list(t_token_node *head);

#endif