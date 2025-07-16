#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"

char * remove_quote(char *str)
{
    int position = 0;
    int current_position = -1;
    char quote;
    
    quote = str[0];
    if (!(quote == '\"' || quote == '\''))
        return (str);

    while(str[position])
    {
        if(str[position] == quote)
            current_position = position;
        else if(str[position] == '\0')
            break;
        position++;
    }
    if (current_position == -1)
        return (str);
    return (ft_substr(str, 1, current_position - 1));
}

void execute(t_node *node, t_minishell *shell_info)
{
    if (!node) return;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (node->type == PIPE)
    {
        execute_pipe((t_pipe_node *)node, shell_info);
        return;
    }
    else if(node->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)node;
        
        if (!replace_cmd_args(cmd, shell_info))
        {
            shell_info->status = 1;
            return;
        }
       
        if (cmd->cmd && is_builtint((t_cmd_node *)cmd))
        {
            int stdout_fd;
            int stdin_fd;
            stdout_fd = dup(STDOUT_FILENO);
            stdin_fd = dup(STDIN_FILENO);
            redirection_handler(cmd, shell_info);
            builtin_handler(cmd, &shell_info->envp, &shell_info->status);
            dup2(stdout_fd, STDOUT_FILENO);
            dup2(stdin_fd, STDIN_FILENO);
            close(stdout_fd);
            close(stdin_fd);
            signal(SIGINT, sig_c);
            signal(SIGQUIT, SIG_IGN);    
            return;
        }
        external_command(cmd, shell_info);
    }
} 