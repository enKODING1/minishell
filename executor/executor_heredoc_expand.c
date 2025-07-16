/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:30:23 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:44:13 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	write_status_variable(int fd, t_minishell *shell_info)
{
	char	*status_str;
	int		len;

	status_str = ft_itoa(shell_info->status);
	len = 0;
	while (status_str[len])
		len++;
	write(fd, status_str, len);
	free(status_str);
}

static void	write_env_variable(int fd, char *line, int *i,
		t_minishell *shell_info)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i + 1;
	while (line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
		(*i)++;
	var_name = ft_substr(line, start, *i - start + 1);
	if (!var_name)
		return ;
	var_value = search_envp(var_name, shell_info->envp);
	if (var_value)
		write(fd, var_value, ft_strlen(var_value));
	free(var_name);
	free(var_value);
}

void	expand_and_write_line(int fd, char *line, t_minishell *shell_info)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (i > start)
				write(fd, line + start, i - start);
			if (line[i + 1] == '?')
			{
				write_status_variable(fd, shell_info);
				i += 2;
				start = i;
				continue ;
			}
			write_env_variable(fd, line, &i, shell_info);
			start = i + 1;
		}
	}
	if (i > start)
		write(fd, line + start, i - start);
	write(fd, "\n", 1);
}
