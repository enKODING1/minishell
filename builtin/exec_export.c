/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:33:03 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 20:51:32 by jinwpark         ###   ########.fr       */
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
	size_t	i;
	size_t	len;
	char	**tmp_list;

	i = 0;
	len = ft_arglen(envp_list);
	tmp_list = malloc(sizeof(char *) * (len + 2));
	if (!envp_list)
		return (NULL);
	while (i < len)
	{
		tmp_list[i] = ft_strdup(envp_list[i]);
		i++;
	}
	tmp_list[len] = ft_strdup(arg);
	tmp_list[len + 1] = NULL;
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
	int		j;

	j = 0;
	i = 0;
	tmp_list = NULL;

	// if (argv[0][0] == '=')
	// {
	// 	exec_error_handler(2, "export", NULL, EXPORT_DOSE_NOT_EQUAL);
	// 	free_envp(tmp_list);
	// }
	if (ft_arglen(argv) == 0)
		echo_export(*envp_list, STDOUT_FILENO);
	else
	{
		tmp_list = add_envp(argv[0], *envp_list);
		free_envp(*envp_list);
		*envp_list = tmp_list;
	}
}
