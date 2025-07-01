#include "builtin.h"
// echo -nasdf 이렇게 해버리면 -nasdf 그대로 출력 됨
int find_message(char **argv)
{
    int i;

    i = 1;
    while (argv[i] && ft_strncmp(argv[i],"-n", 3) == 0) // -e 같은 옵션이 들어오면 어떻게 처리해야하나...
        i++;
    return i;
}

void exec_echo(int *fd, char **argv)
{
    int option;
    int i;
    // 환경 변수에 대해서도 처리해야함 
    i = find_message(argv);
    option = (i > 1);
    if (argv[i] == NULL)
    {
        if (option == 0)
            ft_putstr_fd("\n", fd[1]);
        return ;
    }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], fd[1]);
        if (argv[i + 1] != NULL)
            ft_putstr_fd(" ", fd[1]);
        i++;
    }
    if (option == 0)
        ft_putstr_fd("\n", fd[1]);
}