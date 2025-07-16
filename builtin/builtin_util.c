/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:39:29 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 22:16:39 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char		*remove_quote(char *str);

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

static char	*get_value(char *env_str, size_t len)
{
	char	*value;
	char	*removed;

	value = ft_strdup(env_str + len + 1);
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

char	*search_envp(char *target, char **envp_list)
{
	size_t	len;
	int		i;

	if (!target || !envp_list)
		return (NULL);
	len = ft_strlen(target);
	i = 0;
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], target, len) == 0
			&& envp_list[i][len] == '=')
			return (get_value(envp_list[i], len));
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

	argv = cmd->args;
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		exec_echo(argv, status);
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
}
