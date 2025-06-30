#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "../exec/exec.h"
#include "libft.h"
#include <readline/readline.h>   // readline 사용을 위해 추가
#include <readline/history.h>   // add_history 사용을 위해 추가
#define TEXT_COLOR "\033[38;2;0;255;150m"
#define BORDER_COLOR "\033[38;2;255;0;140m"
#define RESET_COLOR "\033[0m"

char **envp_list;



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

static void init_envp(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;

    envp_list = (char **)malloc(sizeof(char *) * (i + 1));
    if (!envp_list)
        exit(1);
    i = 0;
    while (envp[i])
    {
        envp_list[i] = ft_strdup(envp[i]);
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
}

static void free_envp_tmp()
{
    int i = 0;
    while (envp_list && envp_list[i])
    {
        free(envp_list[i]);
        i++;
    }
    free(envp_list);
}

void free_argv(char **argv)
{
    int i = 0;
    if (!argv)
        return;
    while(argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

// 간단한 스페이스 기준 문자열 파서
char **parse_input(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(1);
    }

    line[strcspn(line, "\n")] = 0;

    token = strtok(line, " ");
    while (token != NULL)
    {
        tokens[position] = ft_strdup(token);
        position++;
        if (position >= bufsize)
        {
            fprintf(stderr, "minishell: too many arguments\n");
            exit(1);
        }
        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    char **args;
    int fd[3];

    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    fd[2] = STDERR_FILENO;

    (void)argc;
    (void)argv;
    print_edge_shell_banner_with_style();
    init_envp(envp);
    set_sig();
    while (1)
    {
        line = readline("edgeshell> ");
        if (line == NULL)
        {
            ft_putendl_fd("exit", STDOUT_FILENO);
            break;
        }
        if (*line)
            add_history(line);
        args = parse_input(line);
        if (args[0] == NULL)
        {
            free_argv(args);
            free(line);
            continue;
        }
        if (ft_strncmp(args[0], "echo",4) == 0)
            exec_echo(fd, args);
        else if (ft_strncmp(args[0], "cd",2) == 0)
            exec_cd(fd, args);
        else if (ft_strncmp(args[0], "pwd",3) == 0)
            exec_pwd(fd, args);
        else if (ft_strncmp(args[0], "export",6) == 0)
            exec_export(fd, args);
        else if (ft_strncmp(args[0], "unset",5) == 0)
            exec_unset(fd, args);
        else if (ft_strncmp(args[0], "env",3) == 0)
            exec_env(fd);
        else if (ft_strncmp(args[0], "exit",4) == 0)
            exec_exit(fd, args);
        else if (args[0])
            printf("edgeshell: command not found: %s\n", args[0]);

        free_argv(args);
        
        free(line);
    }
    free_envp_tmp();
    return (0);
}