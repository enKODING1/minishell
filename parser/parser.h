#ifndef PARSER_H
#define PARSER_H

#include "libft.h"
#include "lexer.h"
#include <stdio.h>

typedef struct s_token_node{
    t_token_type *token;
    struct s_token_node *next;
}t_token_node;

typedef enum e_node_type { 
    NODE_PIPE, NODE_CMD 
} t_node_type;

typedef struct s_node {
     t_node_type type; 
} t_node;

typedef struct s_redir { 
    t_token type; 
    char *filename; 
    struct s_redir *next; 
} t_redir;

typedef struct s_cmd_node { 
    t_node_type type; 
    char *cmd; 
    char **args; 
    t_redir *redirs; 
} t_cmd_node;

typedef struct s_pipe_node { 
    t_node_type type; 
    t_node *left; 
    t_node *right; 
} t_pipe_node;

typedef struct t_parser {
    t_token_node *current_token;
    int has_error;
} t_parser;

/* parser main function */
t_node *parse_pipe(t_parser *parser);
t_node *parse_cmd(t_parser *parser);
t_redir *parse_redirs(t_parser *parser);

/* parser utils */
void parser_init(t_parser *parser, t_token_node *tok_head);
t_token_type * peek_token(t_parser *parser);
void consume_token(t_parser *parser);
void free_token_list(t_token_node *head);
void free_ast(t_node *node);
void print_ast(t_node *node, int indent);

/* token list */
t_token_node *create_token_list(t_lexer *lexer);
t_token_node *create_token_node(t_token_type *tok);
int add_token_node(t_token_node **head, t_token_node *tok);
void print_token_list(t_token_node *head);

#endif