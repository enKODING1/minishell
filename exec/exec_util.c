#include "exec.h"

int *fd_init()
{
    int *fd;

    fd = ft_calloc(sizeof(int), 3);
    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    fd[2] = STDERR_FILENO;
    return (fd);
}

char **get_envp_list(char **envp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    envp_list = malloc(sizeof(char *) * (ft_arglen(envp) + 1));
    if (!envp_list)
        return (NULL);
    while(envp[i])
    {
        envp_list[i] = ft_strdup(envp[i]);
        i++;
    }
    envp_list[i] = NULL;
    return (envp_list);
}