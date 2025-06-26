#include "builtin.h"

void exec_cd(int *fd, char **argv)
{
    int num;
    char *home_path;
    if (ft_arglen(argv) > 2)
    {
        exec_error_handler(fd[2],"cd",NULL,CD_ARG_ERROR); // 절대경로와 상대경로만 다룬다 하니깐 그 이상의 인자를 받는다면 에러처리
        return ;
    }
    if (argv[1] == NULL || argv[1][0] == '\0')
    {
        home_path = getenv("HOME");
        if(!home_path)
        {
            exec_error_handler(fd[2], "cd", NULL, ": HOME NOT SET \n");
            return ;
        }
        chdir(home_path);
        return ;
    }
    num = chdir(argv[1]);
    if (num < 0)
        exec_cd_error_handler(fd[2], "cd", argv[1], CD_DOES_NOT_EXIT_ERROR);
    free(home_path);
}