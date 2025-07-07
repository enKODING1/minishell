#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void handle_in_redir(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("open error\n");
        exit(0);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void handle_out_redir(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("open error\n");
        exit(0);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void handle_append_redir(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf("open error\n");
        exit(0);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void redirection_handler(t_cmd_node *cmd_node)
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
        //heredoc구현하기
        redir = redir->next;
    }
} 