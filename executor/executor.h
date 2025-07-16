/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:41:50 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:41:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <signal.h>
# include <termios.h>
# include <wait.h>

# define NOT_FOUND_CMD 127

typedef struct s_minishell
{
	char	**envp;
	int		status;
}			t_minishell;

// 환경 변수 관련
char		**init_envp(char **envp);
void		free_envp_tmp(char **envp_list);
char		*shell_lv_up(char **envp_list);
char		**main_init(int argc, char **argv, char **envp);

// 명령어 실행 및 경로
char		*get_cmd_path(char *cmd, char **envp);
void		run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp);
void		external_command(t_cmd_node *cmd_node, t_minishell *shell_info);
void		execute_pipe_command(t_cmd_node *cmd_node, t_minishell *shell_info);

// 유틸리티 함수들
void		free_cmd_args(char **args);
char		**replace_cmd_args(t_cmd_node *cmd, t_minishell *shell_info);
void		cleanup_resources(char *line, t_node *ast_root,
				t_token_node *tok_head, t_lexer *lexer);

// 리다이렉션
void		redirection_handler(t_cmd_node *cmd_node, t_minishell *shell_info);

// heredoc 관련
void		handle_heredoc(const char *limiter, t_minishell *shell_info);

// heredoc 확장 관련
void		expand_and_write_line(int fd, char *line, t_minishell *shell_info);

// 파이프 및 실행
void		execute_pipe(t_pipe_node *pipe_node, t_minishell *shell_info);
void		execute_pipe_left_child(t_pipe_node *pipe_node,
				t_minishell *shell_info, int *pipefd);
void		execute_pipe_right_child(t_pipe_node *pipe_node,
				t_minishell *shell_info, int *pipefd);
void		execute(t_node *node, t_minishell *shell_info);

// 시그널 및 터미널
void		sig_c(int sig);
void		set_printf_off(void);
void		set_sig(void);
void		set_printf_on(void);
void		pipe_signal(int left_status, int right_status, int *status);
void		external_signal(int *status);
#endif
