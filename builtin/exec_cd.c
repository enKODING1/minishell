/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:04:47 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 21:42:06 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	set_env(char *key, char *value, char **envp_list)
{
	size_t	key_len;
	char	*key_eq;
	char	*new_entry;
	int		i;

	key_eq = ft_strjoin(key, "=");
	new_entry = ft_strjoin(key_eq, value);
	free(key_eq);
	i = 0;
	key_len = ft_strlen(key);
	while (envp_list && envp_list[i])
	{
		if (ft_strncmp(envp_list[i], key, key_len) == 0
			&& envp_list[i][key_len] == '=')
		{
			free(envp_list[i]);
			envp_list[i] = new_entry;
			return ;
		}
		i++;
	}
	free(new_entry);
}

char	*get_path_from_env(char *str, char **envp_list, int fd)
{
	char	*path;
	char	*error_msg;

	path = search_envp(str, envp_list);
	if (!path)
	{
		error_msg = ft_strjoin(str, " NOT SET \n");
		exec_error_handler(fd, "cd :", NULL, error_msg);
		free(error_msg);
		return (NULL);
	}
	return (path);
}

char	*set_path(char **argv, int fd, int *is_minus, char **envp_list)
{
	char	*path;

	if (ft_arglen(argv) > 2)
	{
		exec_error_handler(fd, "cd", NULL, CD_ARG_ERROR);
		return (NULL);
	}
	if (argv[1] == NULL || argv[1][0] == '\0' || argv[1][0] == '~')
		path = get_path_from_env("HOME", envp_list, fd);
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		path = get_path_from_env("OLDPWD", envp_list, fd);
		*is_minus = 1;
	}
	else
		path = argv[1];
	return (path);
}

void	exec_cd(int *fd, char **argv, char **envp_list)
{
	char	*path;
	char	*old_path;
	int		num;
	int		is_minus;

	old_path = search_envp("PWD", envp_list);
	is_minus = 0;
	path = set_path(argv, fd[2], &is_minus, envp_list);
	if (!path)
		return ;
	num = chdir(path);
	if (num < 0)
	{
		free(old_path);
		exec_error_handler(fd[2], "cd", path, CD_DOES_NOT_EXIT_ERROR);
		return ;
	}
	set_env("OLDPWD", old_path, envp_list);
	path = getcwd(NULL, 0);
	set_env("PWD", path, envp_list);
	if (is_minus)
		ft_putendl_fd(path, fd[1]);
	free(path);
}
