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

static void execute_pipe_left_child(t_pipe_node *pipe_node, t_minishell *shell_info, int *pipefd)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    if (pipe_node->left->type == NODE_PIPE)
    {
        execute_pipe((t_pipe_node *)pipe_node->left, shell_info);
    } else if (pipe_node->left->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)pipe_node->left;
        if (!cmd || !cmd->cmd) exit(0);
        
        // 기존 args 백업 및 새로운 args 생성
        char **old_args = cmd->args;
        char **new_args = ft_argv_filter(cmd->args, shell_info->envp, &shell_info->status);
        
        if (!new_args)
            exit(1);  // 메모리 할당 실패
        
        // 기존 args 메모리 해제
        if (old_args) {
            int i = 0;
            while (old_args[i]) {
                free(old_args[i]);
                i++;
            }
            free(old_args);
        }
        
        // 새로운 args로 교체
        cmd->args = new_args;
        if (cmd->cmd && is_builtint(cmd))
        {
            redirection_handler(cmd, shell_info);
            builtin_handler(cmd, &shell_info->envp, &shell_info->status);
            exit(0);
        }
        else
            execute_pipe_command((t_cmd_node *)pipe_node->left, shell_info);
    }
    exit(0);
}

static void execute_pipe_right_child(t_pipe_node *pipe_node, t_minishell *shell_info, int *pipefd)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    if (pipe_node->right->type == NODE_PIPE)
    {
        execute_pipe((t_pipe_node *)pipe_node->right, shell_info);
    } else if (pipe_node->right->type == NODE_CMD)
    {
        t_cmd_node *cmd = (t_cmd_node *)pipe_node->right;
        
        // 기존 args 백업 및 새로운 args 생성
        char **old_args = cmd->args;
        char **new_args = ft_argv_filter(cmd->args, shell_info->envp, &shell_info->status);
        
        if (!new_args)
            exit(1);  // 메모리 할당 실패
        
        // 기존 args 메모리 해제
        if (old_args) {
            int i = 0;
            while (old_args[i]) {
                free(old_args[i]);
                i++;
            }
            free(old_args);
        }
        
        // 새로운 args로 교체
        cmd->args = new_args;
        if (cmd->cmd && is_builtint(cmd))
        {
            redirection_handler(cmd, shell_info);
            builtin_handler(cmd, &shell_info->envp, &shell_info->status);
            exit(0);
        }
        else
            execute_pipe_command((t_cmd_node *)pipe_node->right, shell_info);
    }
    exit(0);
}

void execute_pipe(t_pipe_node *pipe_node, t_minishell *shell_info)
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
        execute_pipe_left_child(pipe_node, shell_info, pipefd);
    }
    int right_pid = fork();
    if(right_pid == -1)
    {
        printf("fork error\n");
        return;
    }
    if(right_pid == 0)
    {
        execute_pipe_right_child(pipe_node, shell_info, pipefd);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
    pipe_signal(left_status, right_status, &shell_info->status);     
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
        
        // 기존 args 백업 및 새로운 args 생성
        char **old_args = cmd->args;
        char **new_args = ft_argv_filter(cmd->args, shell_info->envp, &shell_info->status);
        
        if (!new_args)
        {
            shell_info->status = 1;
            return;  // 메모리 할당 실패
        }
        
        // 기존 args 메모리 해제
        if (old_args) {
            int i = 0;
            while (old_args[i]) {
                free(old_args[i]);
                i++;
            }
            free(old_args);
        }
        
        // 새로운 args로 교체
        cmd->args = new_args;
       
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