/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:12:01 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 20:19:40 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	echo_pwd(char *str, int fd)
{
	char	*tmp;

	tmp = ft_substr(str, 4, ft_strlen(str));
	ft_putstr_fd(tmp, fd);
	ft_putstr_fd("\n", fd);
	free(tmp);
}

void	exec_pwd(int *fd,
		char **argv,
		char **envp_list)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (argv[1])
	{
		exec_error_handler(fd[2], "pwd", NULL, " TOO MANY ARG \n");
		return ;
	}
	while (envp_list[i])
	{
		if (ft_strncmp("PWD=", envp_list[i], 4) == 0)
			str = envp_list[i];
		i++;
	}
	if (!str)
	{
		exec_error_handler(fd[2], "pwd", NULL, " HOME NOT SET \n");
		return ;
	}
	else
		echo_pwd(str, fd[1]);
}
