/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:04:47 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:31:58 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	set_env(char *key, char *value, char ***envp_list)
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
	while (*envp_list && (*envp_list)[i])
	{
		if (ft_strncmp((*envp_list)[i], key, key_len) == 0
			&& (*envp_list)[i][key_len] == '=')
		{
			free((*envp_list)[i]);
			(*envp_list)[i] = new_entry;
			return ;
		}
		i++;
	}
	free(new_entry);
}

char	*get_path_from_env(char *str, char **envp_list, int fd, int *status)
{
	char	*path;
	char	*error_msg;

	path = search_envp(str, envp_list);
	if (!path)
	{
		error_msg = ft_strjoin(str, " NOT SET \n");
		exec_error_handler(fd, "cd :", NULL, error_msg);
		free(error_msg);
		*status = 1;
		return (NULL);
	}
	return (path);
}

char	*set_path(char **argv, int *status, int *is_minus, char **envp_list)
{
	char	*path;

	if (ft_arglen(argv) > 1)
	{
		exec_error_handler(STDERR_FILENO, "cd", NULL, CD_ARG_ERROR);
		return (NULL);
	}
	else if (argv[0] == NULL || argv[0][0] == '\0' || (argv[0][0] == '~'
			&& argv[0][1] == '\0'))
		path = get_path_from_env("HOME", envp_list, STDERR_FILENO, status);
	else if (ft_strncmp(argv[0], "~/", 2) == 0)
	{
		path = get_path_from_env("HOME", envp_list, STDERR_FILENO, status);
		chdir(path);
		return (ft_substr(argv[0], 2, ft_strlen(argv[0])));
	}
	else if (argv[0][0] == '-' && argv[0][1] == '\0')
	{
		path = get_path_from_env("OLDPWD", envp_list, STDERR_FILENO, status);
		*is_minus = 1;
	}
	else
		path = argv[0];
	return (path);
}

void	exec_cd(char **argv, char ***envp_list, int *status)
{
	char	*path;
	char	*old_path;
	int		num;
	int		is_minus;

	old_path = search_envp("PWD", *envp_list);
	is_minus = 0;
	path = set_path(argv, status, &is_minus, *envp_list);
	if (!path)
		return ;
	num = chdir(path);
	if (num < 0)
	{
		free(old_path);
		*status = 1;
		exec_error_handler(STDERR_FILENO, "cd", path, CD_DOES_NOT_EXIT_ERROR);
		return ;
	}
	set_env("OLDPWD", old_path, envp_list);
	path = getcwd(NULL, 0);
	set_env("PWD", path, envp_list);
	if (is_minus)
		ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	free(old_path);
}
