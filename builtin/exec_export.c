/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:33:03 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 19:13:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	sort_envp(char **envp)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_arglen(envp);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**add_envp(char *arg, char **envp_list)
{
	int		found_idx;
	int		len;
	char	**tmp_list;
	char	*update_arg;
	char	*key;

	key = ft_find_key(arg);
	update_arg = ft_strdup(arg);
	len = ft_arglen(envp_list);
	tmp_list = malloc(sizeof(char *) * (len + 2));
	if (!envp_list || !tmp_list)
	{
		free(key);
		free(update_arg);
		return (NULL);
	}
	found_idx = find_key_and_copy(key, envp_list, tmp_list);
	if (found_idx == -2)
		return (cleanup_and_fail(tmp_list, key, update_arg));
	if (update_or_add_entry(found_idx, tmp_list, update_arg, len) == -1)
		return (cleanup_and_fail(tmp_list, key, update_arg));
	free(key);
	free(update_arg);
	return (tmp_list);
}

void	echo_export(char **envp_list, int fd)
{
	size_t	j;
	char	**tmp_list;
	char	*key;
	char	*value;

	j = 0;
	tmp_list = get_envp_list(envp_list);
	sort_envp(tmp_list);
	while (tmp_list[j])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_key_value(tmp_list[j++], &key, &value);
		ft_putstr_fd(key, fd);
		if (value != NULL)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		free(key);
		free(value);
	}
	free_envp(tmp_list);
}

void	process_export_args(char **argv, char ***envp_list, int *status, int i)
{
	char	**tmp_list;

	if (ft_option_check(argv[0], status, "export"))
		return ;
	while (argv[++i])
	{
		if (argv[i][0] == '=')
		{
			exec_error_handler(STDERR_FILENO, "export", argv[i],
				"NOT A VALID IDENTIFIER");
			*status = 1;
		}
		else
		{
			tmp_list = add_envp(argv[i], *envp_list);
			if (!tmp_list)
			{
				*status = 1;
				return ;
			}
			free_envp(*envp_list);
			*envp_list = tmp_list;
		}
	}
}

void	exec_export(char *env_vaiable, char **argv, char ***envp_list,
		int *status)
{
	char	**tmp_list;
	int		i;

	i = 0;
	tmp_list = NULL;
	(void)env_vaiable;
	if (ft_arglen(argv) == 0)
		echo_export(*envp_list, STDOUT_FILENO);
	else
		process_export_args(argv, envp_list, status, -1);
}
