#include "executor.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "builtin.h"

static void free_matrix(char **matrix)
{
    int i;
    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        matrix[i] = NULL;
        i++;
    }
    free(matrix);
    matrix = NULL;
}

char *get_cmd_path(char *cmd, char **envp)
{
    char **path_list;
    char *path_with_slash;
    char *full_path;
    int i;
    if (!cmd || !*cmd)
        return (NULL);
    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (envp[i] == NULL)
        return (NULL);
    path_list = ft_split(envp[i] + 5, ':');
    if (!path_list)
        return (NULL);
    i = 0;
    while (path_list[i])
    {
        path_with_slash = ft_strjoin(path_list[i], "/");
        full_path = ft_strjoin(path_with_slash, cmd);
        free(path_with_slash);
        if (access(full_path, X_OK) == 0)
        {
            free_matrix(path_list);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_matrix(path_list);
    return (NULL);
}

void run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp)
{
    char **args;
    int i;
    i = 0;
    while(cmd_node->args[i])
        i++;
    args = (char **)malloc(sizeof(char *) * (1 + i + 1));
    if (!args)
    {
        printf("failed\n");
        return;
    }
    i = 0;
    args[0] = ft_strdup(cmd_node->cmd);
    while(cmd_node->args[i])
    {
        args[i+1] = ft_strdup(cmd_node->args[i]);
        i++;
    }
    args[i+1] = NULL;
    if(execve(cmd_path, args, envp) == -1)
    {
        printf("execve error\n");
        free_matrix(args);
        exit(0);
    }
}

void external_command(t_cmd_node *cmd_node, char **envp, int *status)
{
    int pid;
    char *cmd;

    pid = fork();
    if (pid == -1)
        printf("error run: %s\n", cmd_node->cmd);
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        cmd = get_cmd_path(cmd_node->cmd, envp);
        if (cmd_node->cmd != NULL && cmd == NULL)
        {
            printf("not found command\n");
            return;
        }
        redirection_handler(cmd_node, envp);
        run_command(cmd_node, cmd, envp);
        free(cmd);
        exit(0);
    }
    waitpid(pid, status, 0);
    if((*status & 0x7F) == SIGINT)
        ft_putstr_fd("^C\n", STDERR_FILENO);
    else if((*status & 0x7F) == SIGQUIT)
        ft_putendl_fd("^\\Quit (core dumped)", STDERR_FILENO);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, SIG_IGN);        
}

void execute_pipe_command(t_cmd_node *cmd_node, char **envp)
{
    char *cmd;
    cmd = get_cmd_path(cmd_node->cmd, envp);
    if (cmd_node->cmd != NULL && cmd == NULL)
    {
        printf("not found command\n");
        return ;
    }
    redirection_handler(cmd_node, envp);
    run_command(cmd_node, cmd, envp);
    free(cmd);
} 