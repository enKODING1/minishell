#include "executor.h"

void print_edge_shell_banner_with_style(void)
{
    printf(BORDER_COLOR "┌───────────────────────────────────────────────────────────────────────────────────┐\n" RESET_COLOR);
    printf(BORDER_COLOR "│" RESET_COLOR " Welcome to 42 minishell project.                                                  " BORDER_COLOR "│\n" RESET_COLOR);
    printf(BORDER_COLOR "│" RESET_COLOR "                                                                                   " BORDER_COLOR "│\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "████████ ██████╗  ██████╗ ████████╗     ███████╗██╗  ██╗███████╗██╗     ██╗" RESET_COLOR "       " BORDER_COLOR "│\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "██╔════╝ ██╔══██╗██╔════╝ ██╔════╝      ██╔════╝██║  ██║██╔════╝██║     ██║" RESET_COLOR "      " BORDER_COLOR " │\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "█████╗   ██║  ██║██║  ███╗█████╗        ███████╗███████║█████╗  ██║     ██║" RESET_COLOR "      " BORDER_COLOR " │\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "██╔══╝   ██║  ██║██║   ██║██╔══╝        ╚════██║██╔══██║██╔══╝  ██║     ██║" RESET_COLOR "      " BORDER_COLOR " │\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "████████╗██████╔╝╚██████╔╝████████╗     ███████║██║  ██║███████╗███████╗███████╗" RESET_COLOR " " BORDER_COLOR " │\n" RESET_COLOR);
    printf(BORDER_COLOR "│ " TEXT_COLOR "╚═══════╝╚═════╝  ╚═════╝ ╚═══════╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝" RESET_COLOR " " BORDER_COLOR " │\n" RESET_COLOR);
    printf(BORDER_COLOR "│" RESET_COLOR "                                                                                   " BORDER_COLOR "│\n" RESET_COLOR);
    printf(BORDER_COLOR "│" RESET_COLOR "                                                    .created by SKANG & JINWPARK " BORDER_COLOR "  │\n" RESET_COLOR);
    printf(BORDER_COLOR "└───────────────────────────────────────────────────────────────────────────────────┘\n" RESET_COLOR);
}

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

char	*shell_lv_up(char **envp_list)
{
	char	*target;
	char	*lv_str;
	int		level;

	target = search_envp("SHLVL", envp_list);
	level = ft_atoi(target);
	level++;
	lv_str = ft_itoa(level);
	target = ft_strjoin("SHLVL=", lv_str);
	free(lv_str);
	return (target);
}