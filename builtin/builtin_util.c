#include "builtin.h"

int ft_arglen(char **argv)
{
    int i;

    i = 0;
    while(argv[i] != NULL)
        i++;
    return (i);
}