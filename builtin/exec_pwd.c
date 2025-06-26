#include "builtin.h"

void exec_pwd(int *fd)
{
    char *str;
    str = getcwd(NULL, 0);
    if(!str)
    {
        exec_error_handler(fd[2], "pwd", NULL, ": HOME NOT SET \n");
        return ;
    }
    ft_putstr_fd(str,fd[1]);
    ft_putstr_fd("\n",fd[1]);
    free(str);
}