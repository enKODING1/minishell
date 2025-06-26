#include "builtin.h"
#include "exec.h"
void exec_env(int *fd)
{
    int i;

    i = 0;
    while(envp_list[i])
    {
        ft_putstr_fd(envp_list[i], fd[1]);
        ft_putstr_fd("\n",fd[1]);
        i++;
    }
}