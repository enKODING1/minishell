#include "builtin.h"

void exec_cd_error_handler(int fd,char *command,char *target, char *error_message)
{
    ft_putstr_fd("Edgeshell: ", fd);
    ft_putstr_fd(command, fd);
    ft_putstr_fd(" : ", fd);
    ft_putstr_fd(error_message, fd);
    if(target)
    {
        ft_putstr_fd(" : ", fd);
        ft_putstr_fd(target, fd);
    }
    ft_putstr_fd("\n", fd);
}