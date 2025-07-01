#include "exec.h"

int is_builtint(char *str)
{
    if (!ft_strncmp(str, "echo", 4) 
    || !ft_strncmp(str, "pwd", 3) 
    || !ft_strncmp(str, "cd", 2) 
    || !ft_strncmp(str, "export", 6)
    || !ft_strncmp(str, "unset", 5)
    || !ft_strncmp(str, "env", 3)
    || !ft_strncmp(str, "exit", 4))
        return (1);
    else
        return (0);
}

void builtin_handler(t_command *cmd)
{
    int *fd;
    fd = fd_init();
    if(cmd->output_dir)
    {
        if(cmd->mode) // >>
            fd[1] = open(cmd->output_dir,O_CREAT | O_APPEND | O_RDWR, 0644);
        else // >
            fd[1] = open(cmd->output_dir,O_CREAT | O_TRUNC | O_RDWR, 0644);
    }
    if (!ft_strncmp(cmd->argv[0], "echo", 4))
        exec_echo(fd, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "pwd", 3))
        exec_pwd(fd);
    else if (!ft_strncmp(cmd->argv[0], "cd", 2)) // cd home/minishell
        exec_cd(fd, cmd->argv);
    else if (!ft_strncmp(cmd->argv[0], "export", 6))
        exec_export(fd);
    else if (!ft_strncmp(cmd->argv[0], "unset", 5))
        exec_unset(fd);
    else if (!ft_strncmp(cmd->argv[0], "env", 3))
        exec_env(fd);
    else if (!ft_strncmp(cmd->argv[0], "exit", 4))
        exec_exit(fd);
}

void exeternal_handler(t_command *cmd)
{
    return ;
}

void exec_handler(t_command *cmd)
{
    if (cmd->next) // 일단 파이프 라인이 있다면 파이프라인까지 고려해서 명령어를 실행시키는걸로 
    {
        exec_pipeline(cmd->next);
    }
    else // 단일 명령어라면
    {// 빌트인인지 아닌지 아니면 외장 변수인지 판별
        if (is_builtin(cmd->argv[0])) // argv[0] 으로 한 근거는 내가 아는 대부분의 명령어는 앞에 명령어가 오기 때문
        {
            builtin_handler(cmd); 
        }    
        else
        {
            external_handler(cmd);
        }
    }
}

int main()
{
    t_command test;
    char **test_argv;

    printf("--- Running test for: pwd >> a.txt ---\n");    
    test_argv = malloc(sizeof(char *) * 2);
    test_argv[0] = strdup("pwd");
    test_argv[1] = NULL;
    test.argv = test_argv;
    test.output_dir = strdup("a.txt"); // 출력 파일 이름
    test.mode = 1;                     // `>>` (append mode)를 의미
    test.input_dir = NULL;
    test.next = NULL;
    builtin_handler(&test);
    printf("--- Test finished. Check the 'a.txt' file. ---\n");
    free(test.argv[0]);
    free(test.argv);
    free(test.output_dir);
    return (0);
}