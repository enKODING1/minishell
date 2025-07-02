# ifndef EXEC_H
# define EXEC_H

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int is_builtint(char *str);

typedef struct s_command
{
    char **argv; // {"ls" "-l"}
    char *input_dir; // 값으론 파일 값 a.txt
    char *output_dir;
    int mode; // 일단 >> 이거만 생각하고 만듦 >> 이거면 1 아니면 0
    struct s_command *next;
} t_command;


# endif