#include "builtin.h"

int has_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void exec_env(int *fd, char **envp_list)
{
    int i;

    i = 0;
    while(envp_list[i])
    {
        if(has_equal(envp_list[i]) == 1)
        {
            ft_putstr_fd(envp_list[i], fd[1]);
            ft_putstr_fd("\n",fd[1]);
        }
        i++;
    }
}