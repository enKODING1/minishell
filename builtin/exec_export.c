/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:33:03 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:51:07 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

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
	update_arg = ft_update(arg);
	len = ft_arglen(envp_list);
	tmp_list = malloc(sizeof(char *) * (len + 2));
	if (!envp_list || !tmp_list)
		return (NULL);
	found_idx = find_key_and_copy(key, envp_list, tmp_list);
	update_or_add_entry(found_idx, tmp_list, update_arg, len);
	free(key);
	free(update_arg);
	return (tmp_list);
}

void	echo_export(char **envp_list, int fd)
{
	size_t	j;
	char	**tmp_list;

	j = 0;
	tmp_list = get_envp_list(envp_list);
	sort_envp(tmp_list);
	while (tmp_list[j])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(tmp_list[j], fd);
		j++;
	}
	free_envp(tmp_list);
}

void	exec_export(char **argv, char ***envp_list)
{
	char	**tmp_list;
	int		i;

	i = 0;
	tmp_list = NULL;
	if (ft_arglen(argv) == 0)
		echo_export(*envp_list, STDOUT_FILENO);
	else
	{
		while (argv[i])
		{
			if (argv[i][0] == '=')
			{
				exec_error_handler(STDERR_FILENO, "export", argv[i],
				"NOT A VALID IDENTIFIER");
			}
			else
			{
				tmp_list = add_envp(argv[i], *envp_list);
				free_envp(*envp_list);
				*envp_list = tmp_list;
			}
			i++;
		}
	}
}
