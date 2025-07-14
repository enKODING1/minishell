#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"

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
        if (is_builtint((t_cmd_node *)pipe_node->left))
        {
            redirection_handler((t_cmd_node *)pipe_node->left, envp);
            builtin_handler((t_cmd_node *)pipe_node->left, &envp);
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
        if (((t_cmd_node *)pipe_node)->cmd && is_builtint((t_cmd_node *)pipe_node->right))
        {
            // int stdout_fd;
            // int stdin_fd;
            // stdout_fd = dup(STDOUT_FILENO);
            // stdin_fd = dup(STDIN_FILENO);
            redirection_handler((t_cmd_node *)pipe_node->right, envp);
            builtin_handler((t_cmd_node *)pipe_node->right, &envp);
            // dup2(stdout_fd, STDOUT_FILENO);
            // dup2(stdin_fd, STDIN_FILENO);
            // close(stdout_fd);
            // close(stdin_fd);
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
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
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
    if((right_status & 0xFF) == SIGINT || (left_status & 0xFF) == SIGINT)
        ft_putstr_fd("\n", STDERR_FILENO);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, sig_back);
}

void execute(t_node *node, char ***envp)
{
    if (!node) return;
    if (node->type == PIPE)
    {
        execute_pipe((t_pipe_node *)node, *envp);
        return;
    }
    else if(node->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)node;
        
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
            return;
        }
        external_command(cmd, *envp);
    }
} 