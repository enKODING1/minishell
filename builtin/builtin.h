/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:27:26 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/03 17:05:52 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTIN_H
# define BUILTIN_H

# define CD_OPTION_ERROR "부적절한 옵션 \n cd: 사용법: cd [-L|[-P [-e]] [-@]] [<디렉터리>]"
# define CD_ARG_ERROR "인자가 너무 많음"
# define CD_DOES_NOT_EXIT_ERROR "그런 파일이나 디렉터리가 없습니다"
# define EXPORT_DOSE_NOT_EQUAL "= 이외의 다른 문자가 들어왔습니다"

# include <unistd.h>
# include "libft.h"
# include<signal.h>

char	**get_envp_list(char **envp_list);
char	*search_envp(char *target, char **envp_list);
char	*shell_lv_up(char **envp_list);
void	exec_error_handler(int fd,
			char *command,
			char *target,
			char *error_message);
void	exec_cd(char **argv, char **envp_list);
void	exec_env(char **argv, char **envp_list);
void	exec_echo(char **argv);
void	exec_exit(char **argv);
void	exec_export(char **argv, char ***envp_list);
void	exec_pwd(char **argv, char **envp_list);
void	exec_unset(char **argv, char ***envp_list);
void	free_envp(char **envp_list);
int		ft_arglen(char **argv);

#	endif
