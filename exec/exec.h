# ifndef EXEC_H
# define EXEC_H

#include "libft.h"
#include "builtin.h"
#include <unistd.h>
#include <fcntl.h>

int is_builtint(char *str);
char **get_envp_list(char **envp); // 일단은 exec_util쪽에 만들어 놓자

char **envp_list; // env 명령어를 실행하기 위해 필요한 변수 나중에 main쪽 헤더에 편입 될 예정

typedef struct s_command
{
    char **argv; // {"ls" "-l"}
    char *input_dir; // 값으론 파일 값 a.txt
    char *output_dir;
    int mode; // 일단 >> 이거만 생각하고 만듦 >> 이거면 1 아니면 0
    struct s_command *next;
} t_command;


# endif