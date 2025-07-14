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

static void execute_pipe_left_child(t_pipe_node *pipe_node, char **envp, int *pipefd)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    if (pipe_node->left->type == NODE_PIPE)
    {
        execute_pipe((t_pipe_node *)pipe_node->left, envp);
    } else if (pipe_node->left->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)pipe_node->left;
        int i = 0;
        if (ft_strncmp(cmd->cmd, "echo", 4) != 0)
        {
        while(cmd->args[i])
        {
            if (cmd->args[i][0] == '\"' || cmd->args[i][0] == '\'')
            {
                char *prev_quote = cmd->args[i];
                char *removed_quote = remove_quote(cmd->args[i]);
                if (prev_quote != removed_quote)
                {
                    free(prev_quote);
                    cmd->args[i] = removed_quote;
                } 
            }
            i++;
        }
        }
        if (cmd->cmd && is_builtint(cmd))
        {
            redirection_handler(cmd, envp);
            builtin_handler(cmd, envp);
            exit(0);
        }
        else
            execute_pipe_command((t_cmd_node *)pipe_node->left, envp);
    }
    exit(0);
}

static void execute_pipe_right_child(t_pipe_node *pipe_node, char **envp, int *pipefd)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    if (pipe_node->right->type == NODE_PIPE)
    {
        execute_pipe((t_pipe_node *)pipe_node->right, envp);
    } else if (pipe_node->right->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)pipe_node->right;
        int i = 0;
        if (ft_strncmp(cmd->cmd, "echo", 4) != 0)
        {
        while(cmd->args[i])
        {
            if (cmd->args[i][0] == '\"' || cmd->args[i][0] == '\'')
            {
                char *prev_quote = cmd->args[i];
                char *removed_quote = remove_quote(cmd->args[i]);
                if (prev_quote != removed_quote)
                {
                    free(prev_quote);
                    cmd->args[i] = removed_quote;
                } 
            }
            i++;
        }
        }
        if (cmd->cmd && is_builtint(cmd))
        {
            redirection_handler(cmd, envp);
            builtin_handler(cmd, envp);
            exit(0);
        }
        else
            execute_pipe_command((t_cmd_node *)pipe_node->right, envp);
    }
    exit(0);
}

void execute_pipe(t_pipe_node *pipe_node, char **envp)
{
    int pipefd[2];
    int left_status;
    int right_status;
    if(pipe(pipefd) == -1)
    {
        printf("pipe error\n");
        return;
    }
    int left_pid = fork();
    if(left_pid == -1)
    {
        printf("fork error\n");
        return;
    }
    if(left_pid == 0)
    {
        execute_pipe_left_child(pipe_node, envp, pipefd);
    }
    int right_pid = fork();
    if(right_pid == -1)
    {
        printf("fork error\n");
        return;
    }
    if(right_pid == 0)
    {
        execute_pipe_right_child(pipe_node, envp, pipefd);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
    if((right_status & 0x7F) == SIGINT || (left_status & 0x7F) == SIGINT)
        ft_putstr_fd("^C\n", STDERR_FILENO);
    else if((right_status & 0x7F) == SIGQUIT || (left_status & 0x7F) == SIGQUIT)
        ft_putendl_fd("^\\Quit (core dumped)", STDERR_FILENO);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, SIG_IGN);        
}

void execute(t_node *node, char ***envp)
{
    if (!node) return;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (node->type == PIPE)
    {
        execute_pipe((t_pipe_node *)node, *envp);    
        return;
    }
    else if(node->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)node;
        
        int i = 0;
        if (ft_strncmp(cmd->cmd, "echo", 4) != 0)
        {
        while(cmd->args[i])
        {
            if (cmd->args[i][0] == '\"' || cmd->args[i][0] == '\'')
            {
                char *prev_quote = cmd->args[i];
                char *removed_quote = remove_quote(cmd->args[i]);
                if (prev_quote != removed_quote)
                {
                    // free(prev_quote);
                    cmd->args[i] = removed_quote;
                } 
            }
            i++;
        }
        }

        if (cmd->cmd && is_builtint((t_cmd_node *)cmd))
        {
            int stdout_fd;
            int stdin_fd;
            stdout_fd = dup(STDOUT_FILENO);
            stdin_fd = dup(STDIN_FILENO);
            redirection_handler(cmd, *envp);
            builtin_handler(cmd, envp);
            dup2(stdout_fd, STDOUT_FILENO);
            dup2(stdin_fd, STDIN_FILENO);
            close(stdout_fd);
            close(stdin_fd);
            signal(SIGINT, sig_c);
            signal(SIGQUIT, SIG_IGN);    
            return;
        }
        external_command(cmd, *envp);
    }
} 