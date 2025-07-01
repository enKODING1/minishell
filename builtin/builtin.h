# ifndef BUILTIN_H
# define BUILTIN_H

# define CD_OPTION_ERROR "부적절한 옵션 \n cd: 사용법: cd [-L|[-P [-e]] [-@]] [<디렉터리>]"
# define CD_ARG_ERROR "인자가 너무 많음"
# define CD_DOES_NOT_EXIT_ERROR "그런 파일이나 디렉터리가 없습니다"
# define EXPORT_DOSE_NOT_EQUAL "= 이외의 다른 문자가 들어왔습니다"
#include <unistd.h>
#include "libft.h"
#include "exec.h"
#include <signal.h>

int ft_arglen(char **argv);
void exec_error_handler(int fd,char *command,char *target, char *error_message);
void exec_cd(int *fd, char **argv);
void exec_echo(int *fd, char **argv);
void exec_env(int *fd);
void exec_pwd(int *fd, char **argv);
void exec_unset(int *fd, char **argv);
void exec_exit(int *fd,char **argv);
void exec_export(int *fd, char **argv);
void free_envp(char **envp_list);
void set_sig();
# endif