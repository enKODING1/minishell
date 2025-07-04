# ifndef EXECUTOR_H
# define EXECUTOR_H

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "builtin.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include <termios.h>

#define TEXT_COLOR "\033[38;2;0;255;150m"
#define BORDER_COLOR "\033[38;2;255;0;140m"
#define RESET_COLOR "\033[0m"

void print_edge_shell_banner_with_style(void);
void free_envp_tmp(char **envp_list);
void free_argv(char **argv);
void	free_matrix(char **matrix);
void run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp);
void external_command(t_cmd_node *cmd_node, char **envp);
void execute(t_node *node, char **envp);
void	set_sig(void);
void set_sig_fork(void);
char *get_cmd_path(char *cmd, char **envp);
char **init_envp(char **envp);


# endif