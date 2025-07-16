#include "executor.h"

static int create_pipe_and_fork_left(t_pipe_node *pipe_node, 
									t_minishell *shell_info, int *pipefd)
{
	int	left_pid;

	if (pipe(pipefd) == -1)
	{
		printf("pipe error\n");
		return (-1);
	}
	left_pid = fork();
	if (left_pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	if (left_pid == 0)
		execute_pipe_left_child(pipe_node, shell_info, pipefd);
	return (left_pid);
}

static int fork_right_child(t_pipe_node *pipe_node, 
							t_minishell *shell_info, int *pipefd)
{
	int	right_pid;

	right_pid = fork();
	if (right_pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	if (right_pid == 0)
		execute_pipe_right_child(pipe_node, shell_info, pipefd);
	return (right_pid);
}

void execute_pipe(t_pipe_node *pipe_node, t_minishell *shell_info)
{
	int	pipefd[2];
	int	left_status;
	int	right_status;
	int	left_pid;
	int	right_pid;

	left_pid = create_pipe_and_fork_left(pipe_node, shell_info, pipefd);
	if (left_pid == -1)
		return;
	right_pid = fork_right_child(pipe_node, shell_info, pipefd);
	if (right_pid == -1)
		return;
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	pipe_signal(left_status, right_status, &shell_info->status);
} 