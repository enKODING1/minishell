# ifndef BUILTIN_H
# define BUILTIN_H

# define CD_OPTION_ERROR "부적절한 옵션 \n cd: 사용법: cd [-L|[-P [-e]] [-@]] [<디렉터리>]"
# define CD_ARG_ERROR "인자가 너무 많음"
# define CD_DOES_NOT_EXIT_ERROR "그런 파일이나 디렉터리가 없습니다: "
#include <unistd.h>
#include "libft.h"

int ft_arglen(char **argv);

# endif