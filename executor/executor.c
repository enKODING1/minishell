#include "parser.h"
#include <stdio.h>
#include "builtin.h"
#include <wait.h>
#include <fcntl.h>

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
			redirection_handler(cmd);
			builtin_handler(cmd, envp);
			return;
		}
		else
		external_command(cmd, envp);
    }
}
// char **main_init(int argc, char **argv, char **envp)
// {
//     if(argc != 2)
//         (void) argc;
//     (void) argv;
//     // print_edge_shell_banner_with_style();
//     return (init_envp(envp));
// }
int main(int argc, char **argv, char **envp)
{
    // char *input = "< EOF cat -e | cat -e | cat -e | cat -e | cat >> outfile";
    // char *input = "export a= 'hello world' ";
	// char *input = "cat -e outifle";
	// char *input = "echo 'hello world' > cat -e | cat -e | cat -e > outfile";
	// char **envp_list;
	// envp_list = main_init(argc,argv,envp);
	// set_sig();
	// set_printf_off();
	char input[255];
    while(1)
    {
    
    printf("minishell> ");
    fgets(input, sizeof(input), stdin);
    if (ft_strncmp(input, "exit", 4))
    {
        t_lexer *lexer = new(input);
        t_token_node *tok_head = create_token_list(lexer);

        t_parser parser;
        parser_init(&parser, tok_head);
        // print_token_list(tok_head);
        // printf("--- 파싱 시작 ---\n");
        t_node *ast_root = parse_pipe(&parser);

        if (parser.has_error)
        {
            printf("--- 문법 에러 ---\n");
            // free_ast(ast_root);
        }
        else
        {
            // printf("--- 파싱 완료 ---\n\n");
            // print_ast(ast_root, 0);
            // free_ast(ast_root);
			execute(ast_root, envp);
        }
        free_token_list(tok_head);
        free_lexer(lexer);
    }
	}
    return 0;

}