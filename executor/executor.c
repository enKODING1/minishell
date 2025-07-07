#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <termios.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "parser.h"

char **init_envp(char **envp)
{
    char **envp_list;
    int i = 0;
    while (envp[i])
        i++;

    envp_list = (char **)malloc(sizeof(char *) * (i + 1));
    if (!envp_list)
        exit(1);
    i = 0;
    while (envp[i])
    {
        if(ft_strncmp("SHLVL=", envp[i], 6) != 0)
            envp_list[i] = ft_strdup(envp[i]);
        else
            envp_list[i] = shell_lv_up(envp);
        if (!envp_list[i])
        {
            while (i > 0)
                free(envp_list[--i]);
            free(envp_list);
            exit(1);
        }
        i++;
    }
    envp_list[i] = NULL;
    return envp_list;
}

void free_envp_tmp(char **envp_list)
{
    int i;
    
    i = 0;
    while (envp_list && envp_list[i])
    {
        free(envp_list[i]);
        i++;
    }
    free(envp_list);
}

char	*shell_lv_up(char **envp_list)
{
	char	*target;
	char	*lv_str;
	int		level;

	target = search_envp("SHLVL", envp_list);
	level = ft_atoi(target);
	level++;
	lv_str = ft_itoa(level);
	target = ft_strjoin("SHLVL=", lv_str);
	free(lv_str);
	return (target);
}

static void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

char *get_cmd_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*path_with_slash;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL); 
	}

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL) 
		return (NULL);
	
	path_list = ft_split(envp[i] + 5, ':');
	if (!path_list)
		return (NULL);

	i = 0;
	while (path_list[i])
	{
		path_with_slash = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);

		if (access(full_path, X_OK) == 0)
		{
			free_matrix(path_list);
			return (full_path); 
		}
		free(full_path);
		i++;
	}

	free_matrix(path_list);
	return (NULL); 
}

void redirection_handler(t_cmd_node *cmd_node)
{
	int fd;
	t_redir *redir = cmd_node->redirs;
	while(redir)	
	{
		if (redir->type == IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd == -1)
			{
				printf("open error\n");
				exit(0);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if(redir->type == OUT)
		{
				fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					printf("open error\n");
					exit(0);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
		}
		if (redir->type == APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				printf("open error\n");
				exit(0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		//heredoc구현하기	
		redir = redir->next;
	}
}

void run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp)
{
	char **args;
	int i;
	i = 0;	
	while(cmd_node->args[i])
		i++;
	args = (char **)malloc(sizeof(char *) * (1 + i + 1));
	if (!args)
	{
		printf("failed\n");
		return;
	}
	i = 0;	
	args[0] = ft_strdup(cmd_node->cmd);
	while(cmd_node->args[i])
	{
		args[i+1] = ft_strdup(cmd_node->args[i]);
		i++;
	}
	args[i+1] = NULL;
	
	if(execve(cmd_path, args, envp) == -1)
	{
		printf("execve error\n");
		free_matrix(args);
		exit(0);
	}
}

void external_command(t_cmd_node *cmd_node, char **envp)
{
	int pid;
	char *cmd;
	pid = fork();
	if (pid == -1)
		printf("error run: %s\n", cmd_node->cmd);
	if (pid == 0)
	{
		// child process
		
		cmd = get_cmd_path(cmd_node->cmd, envp);
		// printf("cmd: %s\n", cmd);
		if (cmd == NULL)
		{
			printf("not found command\n");
			return;
		}
		redirection_handler(cmd_node);
		run_command(cmd_node, cmd, envp);	
		free(cmd);
		exit(0);
	}

	waitpid(pid, NULL, 0);
}

void execute_pipe_command(t_cmd_node *cmd_node, char **envp)
{
		char *cmd;
		cmd = get_cmd_path(cmd_node->cmd, envp);
		if (cmd == NULL)
		{
			printf("not found command\n");
			return ;
		}
		redirection_handler(cmd_node);
		run_command(cmd_node, cmd, envp);
		
		free(cmd);
}

void execute_pipe(t_pipe_node *pipe_node, char **envp)
{
		int pipefd[2];

		if(pipe(pipefd) == -1)
		{
			printf("pipe error\n");
			return;
		}

		int left_pid = fork();
		if(left_pid == -1)
		{
			printf("fork error\n");
			return;
		}
		if(left_pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			if (pipe_node->left->type == NODE_PIPE)
			{
				execute_pipe((t_pipe_node *)pipe_node->left, envp);
			}else if (pipe_node->left->type == NODE_CMD)
			{
				if (is_builtint((t_cmd_node *)pipe_node->left))
				{
					redirection_handler((t_cmd_node *)pipe_node->left);
					builtin_handler((t_cmd_node *)pipe_node->left, envp);
					exit(0);
				}
				else
					execute_pipe_command((t_cmd_node *)pipe_node->left, envp);
			}
			exit(0);
		}

		int right_pid = fork();
		if(right_pid == -1)
		{
			printf("fork error\n");
			return;
		}
		if(right_pid == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (pipe_node->right->type == NODE_PIPE)
			{
				execute_pipe((t_pipe_node *)pipe_node->right, envp);
			}else if (pipe_node->right->type == NODE_CMD)
			{
				if (is_builtint((t_cmd_node *)pipe_node->right))
				{
					redirection_handler((t_cmd_node *)pipe_node->right);
					builtin_handler((t_cmd_node *)pipe_node->right, envp);
					exit(0);
				}
				else
					execute_pipe_command((t_cmd_node *)pipe_node->right, envp);
			}
			exit(0);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, NULL, 0);
		waitpid(right_pid, NULL, 0);
}

void execute(t_node *node, char **envp)
{
    if (!node) return;
    if (node->type == PIPE)
    {
        // printf("pipe is not supported yet..\n");
			execute_pipe((t_pipe_node *)node, envp);
			return;
    }
    else if(node->type == NODE_CMD)
    {
        // built in 실행
        /* 
         execve 실행 
         execve는 실행파일의 프로세스로 대체 됨.
        */
	    t_cmd_node *cmd = (t_cmd_node *)node;
		
		if (is_builtint((t_cmd_node *)cmd))	
		{
			int stdout_fd;
			int stdin_fd;

			stdout_fd = dup(STDOUT_FILENO);
			stdin_fd = dup(STDIN_FILENO);
			redirection_handler(cmd);
			builtin_handler(cmd, envp);
			dup2(stdout_fd, STDOUT_FILENO);
			dup2(stdin_fd, STDIN_FILENO);
			close(stdout_fd);
			close(stdin_fd);
			return;
		}
		else
		external_command(cmd, envp);
    }
}

char **main_init(int argc, char **argv, char **envp)
{
    if(argc != 2)
        (void) argc;
    (void) argv;
    // print_edge_shell_banner_with_style();
    return (init_envp(envp));
}

void	sig_c(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


// void	sig_c_fork(int sig)
// {
// 	(void) sig;
// 	ft_putstr_fd("\n", 2);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	sig_back(int sig)
{
	(void) sig;
}

void	set_printf_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

// void set_sig_fork(void)
// {
// 	signal(SIGINT, sig_c_fork);
// 	signal(SIGQUIT, sig_back);
// }

void	set_sig(void)
{
	set_printf_off();
	signal(SIGINT, sig_c);
	signal(SIGQUIT, sig_back);
}


int main(int argc, char **argv, char **envp)
{
	t_lexer *lexer;
    t_token_node *tok_head;
    t_parser parser;
    t_node *ast_root;    
    char **envp_list;
    char *line;
    int is_parser_error;

    envp_list = main_init(argc,argv,envp);
    set_sig();
    // set_printf_off();
    while (1)
    {
        is_parser_error = 0;
        line = readline("minishell> ");
        if (line == NULL)
        {
            ft_putendl_fd("exit", STDOUT_FILENO);
            break;
        }
        if (*line)
            add_history(line);
        lexer = new(line);
        tok_head = create_token_list(lexer);
        parser_init(&parser, tok_head);
        ast_root = parse_pipe(&parser);
        execute(ast_root, envp_list);
        free(line);
        free_token_list(tok_head);
        free_lexer(lexer);
    }
    free_envp_tmp(envp_list);
    return (0);
}