#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "get_next_line.h"

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

void expand_and_write_line(int fd, char *line, char **envp)
{
	int		i;
	int		start;
	char	*var_name;
	char	*var_value;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
				write(fd, line + start, i - start);

			start = i + 1;
			while (line[i + 1] && (isalnum(line[i + 1]) || line[i + 1] == '_'))
				i++;
			
            var_name = ft_substr(line, start, i - start + 1);
            if (!var_name) return; 
			
			var_value = search_envp(var_name, envp);
			if (var_value)
				write(fd, var_value, strlen(var_value));
			
			free(var_name);
			start = i + 1;
		}
		i++;
	}
	
	if (i > start)
		write(fd, line + start, i - start);
	
	write(fd, "\n", 1);
}


static void handle_heredoc(const char *limiter, char **envp)
{
    int temp_fd;
    char *line;
    int diff;
    pid_t pid;
    int status;
    
    temp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    pid = fork();
    if (pid == 0) // 자식 프로세스  
    {
        close(temp_fd);
        temp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_APPEND);
        
        while(1)
        {
            // line = readline("> ");
            ft_putstr_fd("> ", STDERR_FILENO);
            //get_next_line buffer 비워주기 
            line = get_next_line(STDIN_FILENO);
            int i;
            i=0;
            while(line[i] != '\n')
                i++;
            line[i] = '\0';
            if (line == NULL)
            {
                ft_putendl_fd("error heredoc", STDERR_FILENO);
                exit(1);
            }
            
            diff = ft_strncmp(line, limiter, ft_strlen(limiter));
            
            if (diff == 0 && ft_strlen(line) == ft_strlen(limiter))
            {
                free(line);
                break;
            }
            expand_and_write_line(temp_fd, line, envp);
            free(line);
        }
        
        close(temp_fd);
        exit(0);
    }
    else  // 부모 프로세스
    {
        close(temp_fd);
        waitpid(pid, &status, 0);
        
        // 파일을 STDIN으로 리다이렉션
        temp_fd = open("/tmp/heredoc_tmp", O_RDONLY);
        dup2(temp_fd, STDIN_FILENO);
        close(temp_fd);
        unlink("/tmp/heredoc_tmp");
    }
}


void redirection_handler(t_cmd_node *cmd_node, char **envp)
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
            handle_heredoc(redir->filename, envp);
        redir = redir->next;
    }
} 