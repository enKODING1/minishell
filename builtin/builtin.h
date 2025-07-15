/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:27:26 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 00:54:58 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define CD_OPTION_ERROR "bad option"
# define CD_ARG_ERROR "too many arg"
# define CD_DOES_NOT_EXIT_ERROR "no such file or directory"
# define EXPORT_DOSE_NOT_EQUAL "Invalid characters were entered"

# include "libft.h"
# include "parser.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_string_builder
{
	char			*str;
	size_t			len;
	size_t			cap;
}					t_string_builder;

char				**get_envp_list(char **envp_list);
char				*search_envp(char *target, char **envp_list);
void				exec_error_handler(int fd, char *command, char *target,
						char *error_message);
void				exec_cd(char **argv, char ***envp_list, int *status);
void				exec_env(char **argv, char **envp_list, int *status);
void				exec_echo(char **argv, char **envp_list, int *status);
void				exec_exit(char **argv, int *status);
void				exec_export(char *env_vaiable, char **argv,
						char ***envp_list, int *status);
void				exec_pwd(char **argv, char **envp_list, int *status);
void				exec_unset(char **argv, char ***envp_list, int *status);
void				free_envp(char **envp_list);
void				builtin_handler(t_cmd_node *cmd, char ***envp, int *status);
int					ft_arglen(char **argv);
int					is_builtint(t_cmd_node *cmd);
int					expand_env(char *str, char **envp_list,
						t_string_builder *list, int *status);
char				*ft_advanced_substr(char *str, char **envp_list,
						int *status);
char				**ft_argv_filter(char **argv, char **envp_list,
						int *status);
t_string_builder	*builder_init(void);
void				append_char(t_string_builder *sb, char c);
void				append_str(t_string_builder *sb, char *str);
void				free_builder(t_string_builder *sb);
char				*free_return_str(t_string_builder *sb);
char				*ft_find_key(char *arg);
int					handle_double_quote(char **str, char **envp_list,
						t_string_builder *list, int *status);
int					handle_single_quote(char **str, t_string_builder *list,
						int *status);
int					ft_strcmp(char *str1, char *str2);
int					find_key_and_copy(char *key, char **envp_list,
						char **tmp_list);
void				update_or_add_entry(int j, char **tmp_list,
						char *update_arg, int list_len);
void				ft_key_value(char *arg, char **key, char **value);
int					ft_option_check(char *argv, int *status, char *cmd);
void two_free(char *str1, char *str2);
void free_matrix_str(char **matrix);

#endif
