#include "builtin.h"

void exec_pwd(int *fd, char **argv, char **envp_list) // 매개변수 나중에 수정
{
    char *str;
    char *tmp;
    int i;

    i = 0;
    str = NULL;
    if (argv[1])
    {
        exec_error_handler(fd[2], "pwd", NULL, " TOO MANY ARG \n");
        return ;
    }
    while (envp_list[i])
    {
        if (ft_strncmp("PWD=",envp_list[i],4) == 0)
            str = envp_list[i];
        i++;
    }
    if(!str)
    {
        exec_error_handler(fd[2], "pwd", NULL, " HOME NOT SET \n");
        return ;
    }
    else
    {
        tmp = ft_substr(str, 4, ft_strlen(str));
        ft_putstr_fd(tmp,fd[1]);
        ft_putstr_fd("\n",fd[1]);
        free(tmp);
    }
}