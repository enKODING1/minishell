/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:04:47 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 22:26:42 by jinwpark         ###   ########.fr       */
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
		error_msg = ft_strjoin(str, " NOT SET");
		exec_error_handler(fd, "cd ", NULL, error_msg);
		free(error_msg);
		*status = 1;
		return (NULL);
	}
	return (path);
}

int	handle_cd_execution(char *path, char *old_path, int *status)
{
	if (!path)
	{
		two_free(old_path, path);
		return (-1);
	}
	if (chdir(path) < 0)
	{
		*status = 1;
		exec_error_handler(STDERR_FILENO, "cd", path, CD_DOES_NOT_EXIT_ERROR);
		two_free(old_path, path);
		return (-1);
	}
	return (0);
}

void	exec_cd(char **argv, char ***envp_list, int *status)
{
	char	*path;
	char	*old_path;
	int		is_minus;

	old_path = search_envp("PWD", *envp_list);
	is_minus = 0;
	path = set_path(argv, status, &is_minus, *envp_list);
	if (handle_cd_execution(path, old_path, status) == -1)
		return ;
	set_env("OLDPWD", old_path, envp_list);
	free(path);
	path = getcwd(NULL, 0);
	set_env("PWD", path, envp_list);
	if (is_minus)
		ft_putendl_fd(path, STDOUT_FILENO);
	two_free(old_path, path);
	*status = 0;
}
