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

static char **init_envp(char **envp)
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
    return envp_list;
}

static void free_envp_tmp(char **envp_list)
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
//쉘을 실행할때마다 쉘 레벨이 올라가야함
int main(int argc, char **argv, char **envp)
{
    char **envp_list = NULL;
    char *line;
    char **args;     // parse_input으로 전체 라인을 자른 배열
    char *cmd;       // 명령어(첫 번째 토큰)를 저장할 변수
    char **cmd_args; // 명령어를 제외한 나머지 인자들을 가리킬 포인터

    (void)argc;
    (void)argv;
    print_edge_shell_banner_with_style();
    envp_list = init_envp(envp);

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

        // 1. 기존 파서로 라인을 공백 기준 분리 (예: "cd /tmp" -> {"cd", "/tmp", NULL})
        args = parse_input(line);

        // 빈 라인 입력 시 건너뛰기
        if (args[0] == NULL)
        {
            free_argv(args);
            free(line);
            continue;
        }

        // 2. 첫 번째 토큰을 cmd 변수에 저장
        cmd = args[0];
        
        // 3. 두 번째 토큰부터의 주소를 cmd_args에 저장 (이것이 exec 함수들로 넘어갈 인자)
        cmd_args = &args[1];

        // 4. cmd 변수를 기준으로 분기하고, exec 함수에는 cmd_args를 전달
        if (ft_strncmp(cmd, "echo", 5) == 0)
            exec_echo(cmd_args);
        else if (ft_strncmp(cmd, "cd", 3) == 0)
            exec_cd(cmd_args, envp_list);
        else if (ft_strncmp(cmd, "pwd", 4) == 0)
            exec_pwd(cmd_args, envp_list);
        else if (ft_strncmp(cmd, "export", 7) == 0)
            exec_export(cmd_args, &envp_list);
        else if (ft_strncmp(cmd, "unset", 6) == 0)
            exec_unset(cmd_args, &envp_list);
        else if (ft_strncmp(cmd, "env", 4) == 0)
            exec_env(cmd_args, envp_list);
        else if (ft_strncmp(cmd, "exit", 5) == 0)
            exec_exit(cmd_args);
        else if (cmd)
            printf("edgeshell: command not found: %s\n", cmd);
        
        // 5. 메모리 해제 (전체 배열인 args를 해제해야 함)
        free_argv(args);
        free(line);
    }
    free_envp_tmp(envp_list);
    return (0);
}