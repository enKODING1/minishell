/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:08:16 by skang             #+#    #+#             */
/*   Updated: 2025/07/17 00:08:19 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*find_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i] + 5);
}

static char	*search_in_path_list(char *cmd, char **path_list)
{
	char	*path_with_slash;
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		path_with_slash = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_str;
	char	**path_list;
	char	*full_path;

	if (!cmd || !*cmd)
		return (NULL);
	full_path = check_direct_path(cmd);
	if (full_path)
		return (full_path);
	path_str = find_path_variable(envp);
	if (!path_str)
		return (NULL);
	path_list = ft_split(path_str, ':');
	if (!path_list)
		return (NULL);
	full_path = search_in_path_list(cmd, path_list);
	free_matrix(path_list);
	return (full_path);
}
