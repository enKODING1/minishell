/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:39:29 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 01:04:14 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*remove_quote(char *str);

char	**get_envp_list(char **envp_list)
{
	char	**tmp_list;
	int		i;

	i = 0;
	tmp_list = malloc(sizeof(char *) * (ft_arglen(envp_list) + 1));
	if (!tmp_list)
		return (NULL);
	while (envp_list[i])
	{
		tmp_list[i] = ft_strdup(envp_list[i]);
		if (!tmp_list[i])
		{
			while (i > 0)
				free(tmp_list[--i]);
			free(tmp_list);
			return (NULL);
		}
		i++;
	}
	tmp_list[i] = NULL;
	return (tmp_list);
}

void	free_envp(char **envp_list)
{
	int	i;

	i = 0;
	while (envp_list && envp_list[i])
	{
		free(envp_list[i]);
		i++;
	}
	free(envp_list);
}

char	*search_envp(char *target, char **envp_list)
{
	size_t	len;
	int		i;
	char	*value;
	char	*removed;

	if (!target || !envp_list)
		return (NULL);
	i = 0;
	len = ft_strlen(target);
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], target, len) == 0
			&& envp_list[i][len] == '=')
		{
			value = ft_strdup(envp_list[i] + len + 1);
			if (!value)
				return (NULL);
			removed = remove_quote(value);
			if (removed != value)
			{
				free(value);
				value = removed;
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	is_builtint(t_cmd_node *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4) || !ft_strncmp(cmd->cmd, "pwd", 3)
		|| !ft_strncmp(cmd->cmd, "cd", 2) || !ft_strncmp(cmd->cmd, "export", 6)
		|| !ft_strncmp(cmd->cmd, "unset", 5) || !ft_strncmp(cmd->cmd, "env", 3)
		|| !ft_strncmp(cmd->cmd, "exit", 4))
		return (1);
	else
		return (0);
}

void	builtin_handler(t_cmd_node *cmd, char ***envp, int *status)
{
	char	**argv;

	argv = ft_argv_filter(cmd->args, *envp, status);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		exec_echo(argv, *envp, status);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		exec_pwd(argv, *envp, status);
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
		exec_cd(argv, envp, status);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		exec_export(NULL, argv, envp, status);
	else if (!ft_strncmp(cmd->cmd, "unset", 5))
		exec_unset(argv, envp, status);
	else if (!ft_strncmp(cmd->cmd, "env", 3))
		exec_env(argv, *envp, status);
	else if (!ft_strncmp(cmd->cmd, "exit", 4))
		exec_exit(argv, status);
	free_matrix_str(argv);
}
