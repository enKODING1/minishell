/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:22:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 22:23:01 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*handle_home_prefix_path(char *arg, char **envp_list, int *status)
{
	char	*home_path;

	home_path = get_path_from_env("HOME", envp_list, STDERR_FILENO, status);
	if (!home_path)
		return (NULL);
	chdir(home_path);
	free(home_path);
	return (ft_substr(arg, 2, ft_strlen(arg) - 2));
}

static int	is_home_path(char *arg)
{
	if (arg == NULL || arg[0] == '\0')
		return (1);
	if (arg[0] == '~' && arg[1] == '\0')
		return (1);
	if (ft_strlen(arg) == 2 && ft_strncmp(arg, "~/", 2) == 0)
		return (1);
	return (0);
}

char	*set_path(char **argv, int *status, int *is_minus, char **envp_list)
{
	char	*arg;

	if (ft_arglen(argv) > 1)
	{
		exec_error_handler(STDERR_FILENO, "cd", NULL, CD_ARG_ERROR);
		*status = 1;
		return (NULL);
	}
	arg = argv[0];
	if (is_home_path(arg))
		return (get_path_from_env("HOME", envp_list, STDERR_FILENO, status));
	if (ft_strlen(arg) > 2 && ft_strncmp(arg, "~/", 2) == 0)
		return (handle_home_prefix_path(arg, envp_list, status));
	if (arg[0] == '-' && arg[1] == '\0')
	{
		*is_minus = 1;
		return (get_path_from_env("OLDPWD", envp_list, STDERR_FILENO, status));
	}
	return (ft_strdup(arg));
}
