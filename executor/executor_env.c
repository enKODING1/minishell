#include "executor.h"
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "builtin.h"

char **init_envp(char **envp)
{
    char **envp_list;
    int i = 0;
    while (envp[i])
        i++;

    envp_list = (char **)malloc(sizeof(char *) * (i + 1));
    if (!envp_list)
        exit(1);
    i = 0;
    while (envp[i])
    {
        if(ft_strncmp("SHLVL=", envp[i], 6) != 0)
            envp_list[i] = ft_strdup(envp[i]);
        else
            envp_list[i] = shell_lv_up(envp);
        if (!envp_list[i])
        {
            while (i > 0)
                free(envp_list[--i]);
            free(envp_list);
            exit(1);
        }
        i++;
    }
    envp_list[i] = NULL;
    return envp_list;
}

void free_envp_tmp(char **envp_list)
{
    int i;
    i = 0;
    while (envp_list && envp_list[i])
    {
        free(envp_list[i]);
        i++;
    }
    free(envp_list);
}

char *shell_lv_up(char **envp_list)
{
    char *target;
    char *lv_str;
    int level;

    target = search_envp("SHLVL", envp_list);
    level = ft_atoi(target);
    level++;
    lv_str = ft_itoa(level);
    target = ft_strjoin("SHLVL=", lv_str);
    free(lv_str);
    return (target);
}

char **main_init(int argc, char **argv, char **envp)
{
    if(argc != 2)
        (void) argc;
    (void) argv;
    return (init_envp(envp));
} 