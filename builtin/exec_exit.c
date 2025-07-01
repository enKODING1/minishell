#include "builtin.h"

static int ft_check(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(!('0' <= str[i] && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

void exec_exit(int *fd,char **argv)
{
    int i;
    int exit_num;
    i = 1; // 일단 1로 추후 0으로 수정

    ft_putendl_fd("exit",fd[1]);
    if(argv[1] == NULL)
        exit(0);
    if (ft_arglen(argv) > 2)
    {
        exec_error_handler(fd[2],"exit",NULL,"TOO MANY ARG");
        return ;
    }
    while (argv[i])
    {
        if (ft_check(argv[i]))
        {
            exec_error_handler(fd[2],"exit",NULL,"INVALID ARG");
            exit(0);
            return ;
        }
        i++;
    }
    exit_num = ft_atoi(argv[1]);
    exit(exit_num % 256);
}