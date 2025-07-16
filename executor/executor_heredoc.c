/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:30:41 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/16 23:30:50 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "cm_readline.h"
#include "executor.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

static void	cm_clear_buffer(void)
{
	int		dev_null_fd;
	char	*dummy_line;

	dev_null_fd = open("/dev/null", O_RDONLY);
	if (dev_null_fd == -1)
		return ;
	dummy_line = cm_readline(dev_null_fd);
	if (dummy_line)
		free(dummy_line);
	close(dev_null_fd);
}

static char	*read_heredoc_line(void)
{
	char	*line;
	int		i;

	ft_putstr_fd("> ", STDERR_FILENO);
	line = cm_readline(STDIN_FILENO);
	if (line == NULL)
	{
		ft_putendl_fd("\nminishell: warning", STDERR_FILENO);
		exit(1);
	}
	i = 0;
	while (line[i] != '\n')
		i++;
	line[i] = '\0';
	return (line);
}

static void	heredoc_child_process(const char *limiter, t_minishell *shell_info)
{
	int		temp_fd;
	char	*line;
	int		diff;

	temp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_APPEND);
	while (1)
	{
		line = read_heredoc_line();
		diff = ft_strncmp(line, limiter, ft_strlen(limiter));
		if (diff == 0 && ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		expand_and_write_line(temp_fd, line, shell_info);
		free(line);
	}
	close(temp_fd);
	exit(0);
}

static void	heredoc_parent_process(int temp_fd, pid_t pid)
{
	int	status;

	close(temp_fd);
	waitpid(pid, &status, 0);
	cm_clear_buffer();
	temp_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	unlink("/tmp/heredoc_tmp");
}

void	handle_heredoc(const char *limiter, t_minishell *shell_info)
{
	int		temp_fd;
	pid_t	pid;

	temp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		close(temp_fd);
		heredoc_child_process(limiter, shell_info);
	}
	else
	{
		heredoc_parent_process(temp_fd, pid);
	}
}
