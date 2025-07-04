#include "parser.h"

static void parse_cmd_args(t_parser *parser, t_cmd_node *cmd_head, int *i) {
    if (peek_token(parser)->type == WORD) {
        if (cmd_head->cmd == NULL)
            cmd_head->cmd = peek_token(parser)->value;
        else
            cmd_head->args[(*i)++] = peek_token(parser)->value;
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
    cmd_head->args = (char **)ft_calloc(20, sizeof(char *));

    int i = 0;
    while (peek_token(parser) && peek_token(parser)->type != PIPE && peek_token(parser)->type != END)
    {
        if (peek_token(parser)->type == WORD)
            parse_cmd_args(parser, cmd_head, &i);
        else if (peek_token(parser)->type >= HEREDOC && peek_token(parser)->type <= IN)
        {
            if (!parse_cmd_redirs(parser, cmd_head))
                return NULL;
        }
        else break;
    }
    return (t_node *)cmd_head;
}