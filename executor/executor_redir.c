#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void open_and_redirect(const char *filename, int flags, int target_fd)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		printf("open error\n");
		exit(0);
	}
	dup2(fd, target_fd);
	close(fd);
}

static void handle_in_redir(const char *filename)
{
	open_and_redirect(filename, O_RDONLY, STDIN_FILENO);
}

static void handle_out_redir(const char *filename)
{
	open_and_redirect(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
}

static void handle_append_redir(const char *filename)
{
	open_and_redirect(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}




void redirection_handler(t_cmd_node *cmd_node, t_minishell *shell_info)
{
    t_redir *redir = cmd_node->redirs;
    while(redir)
    {
        if (redir->type == IN)
            handle_in_redir(redir->filename);
        if (redir->type == OUT)
            handle_out_redir(redir->filename);
        if (redir->type == APPEND)
            handle_append_redir(redir->filename);
        if (redir->type == HEREDOC)
            handle_heredoc(redir->filename, shell_info);
        redir = redir->next;
    }
} 