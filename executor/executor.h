#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"

// 환경 변수 관련
char **init_envp(char **envp);
void free_envp_tmp(char **envp_list);
char *shell_lv_up(char **envp_list);
char **main_init(int argc, char **argv, char **envp);

// 명령어 실행 및 경로
char *get_cmd_path(char *cmd, char **envp);
void run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp);
void external_command(t_cmd_node *cmd_node, char **envp);
void execute_pipe_command(t_cmd_node *cmd_node, char **envp);

// 리다이렉션
void redirection_handler(t_cmd_node *cmd_node);

// 파이프 및 실행
void execute_pipe(t_pipe_node *pipe_node, char **envp);
void execute(t_node *node, char **envp);

// 시그널 및 터미널
void sig_c(int sig);
void sig_back(int sig);
void set_printf_off(void);
void set_sig(void);

#endif 