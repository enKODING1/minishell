#include "parser.h"
#include <stdlib.h>
#include "libft.h"

#define INIT_ARGC 8

static char **ft_args_realloc(char **old, int old_cap, int new_cap) {
    char **new_args = (char **)ft_calloc(new_cap, sizeof(char *));
    if (!new_args) exit(1);
    for (int j = 0; j < old_cap; ++j)
        new_args[j] = old[j];
    free(old);
    return new_args;
}

static void parse_cmd_args(t_parser *parser, t_cmd_node *cmd_head, int *i, int *cap) {
    if (peek_token(parser)->type == WORD) {
        if (cmd_head->cmd == NULL)
            cmd_head->cmd = ft_strdup(peek_token(parser)->value);
        else {
            if (*i + 2 >= *cap) {
                int new_cap = (*cap) * 2;
                cmd_head->args = ft_args_realloc(cmd_head->args, *cap, new_cap);
                *cap = new_cap;
            }
            cmd_head->args[(*i)++] = ft_strdup(peek_token(parser)->value);
            cmd_head->args[*i] = NULL;
        }
        consume_token(parser);
    }
}

static int parse_cmd_redirs(t_parser *parser, t_cmd_node *cmd_head) {
    t_redir *redir = parse_redirs(parser);
    if (parser->has_error)
        return 0;
    if (!cmd_head->redirs) {
        cmd_head->redirs = redir;
    } else {
        t_redir *current = cmd_head->redirs;
        while(current->next)
            current = current->next;
        current->next = redir;
    }
    return 1;
}

t_node *parse_cmd(t_parser *parser)
{
    t_cmd_node *cmd_head = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
    cmd_head->type = NODE_CMD;
    int cap = INIT_ARGC;
    cmd_head->args = (char **)ft_calloc(cap, sizeof(char *));
    if (!cmd_head->args) exit(1);

    int i = 0;
    while (peek_token(parser) && peek_token(parser)->type != PIPE && peek_token(parser)->type != END)
    {
        if (peek_token(parser)->type == WORD)
            parse_cmd_args(parser, cmd_head, &i, &cap);
        else if (peek_token(parser)->type >= HEREDOC && peek_token(parser)->type <= IN)
        {
            if (!parse_cmd_redirs(parser, cmd_head)) {
                free_cmd_node(cmd_head);
                return NULL;
            }
        }
        else break;
    }
    cmd_head->args[i] = NULL;
    return (t_node *)cmd_head;
}