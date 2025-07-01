#include "builtin.h"

char ** add_envp(char *arg)
{
    size_t i;
    size_t len;
    char **tmp_list;

    i = 0;
    len = ft_arglen(envp_list);
    tmp_list = malloc(sizeof(char *) * (len + 2));
    if (!envp_list)
        return (NULL);
    while (i < len)
    {
        tmp_list[i] = ft_strdup(envp_list[i]);
        i++;
    }
    tmp_list[len] = ft_strdup(arg);
    tmp_list[len + 1] = NULL;
    return (tmp_list);
}