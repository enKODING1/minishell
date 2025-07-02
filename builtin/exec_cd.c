#include "builtin.h"

// PWD,OLD_PWD 값을 바꾸고 cd의 다양한 상황에 대해서 대처하라
// cd -가 먹통이 되는 상황 발생
void set_env(char *key, char *value, char **envp_list)
{
    size_t key_len;
    char *key_eq;
    char *new_entry;
    int i;

    key_eq = ft_strjoin(key,"=");
    if (!key_eq)
        return ;
    new_entry = ft_strjoin(key_eq, value);
    if (!new_entry)
    {
        free(key_eq);
        return ;
    }
    free(key_eq);
    i = 0;
    key_len = ft_strlen(key);
    while(envp_list && envp_list[i])
    {
        if(ft_strncmp(envp_list[i],key,key_len) == 0 && envp_list[i][key_len] == '=')
        {
            free(envp_list[i]);
            envp_list[i] = new_entry;
            return ;
        }
        i++;
    }
    free(new_entry);
}

char *search_envp(char *target, char **envp_list)
{
    size_t len;
    int i;

    if (!target || !envp_list)
        return (NULL);
    i = 0;
    len = ft_strlen(target);
    while(envp_list[i])
    {
        if(ft_strncmp(envp_list[i], target, len) == 0 && envp_list[i][len] == '=')
            return envp_list[i] + len + 1;
        i++;
    }
    return (NULL);
}

void exec_cd(int *fd, char **argv, char **envp_list)
{
    int num;
    int is_minus;
    char *path;
    char *old_path;
    
    old_path = search_envp("PWD", envp_list);
    is_minus = 0;
    if (ft_arglen(argv) > 2)
    {
        exec_error_handler(fd[2],"cd",NULL,CD_ARG_ERROR); // 절대경로와 상대경로만 다룬다 하니깐 그 이상의 인자를 받는다면 에러처리
        return ;
    }
    if (argv[1] == NULL || argv[1][0] == '\0' || argv[1][0] == '~')
    {
        path = search_envp("HOME", envp_list);
        if(!path)
        {
            exec_error_handler(fd[2], "cd", NULL, ": HOME NOT SET \n");
            return ;
        }
    }
    else if (argv[1][0] == '-' && argv[1][1] == '\0')
    {
        path = search_envp("OLDPWD", envp_list);
        is_minus = 1;
        if(!path)
        {
            exec_error_handler(fd[2], "cd", NULL, ": OLDPWD NOT SET \n");
            return ;
        }
    }
    else
        path = argv[1];
    num = chdir(path);
    if (num < 0)
    {
        free(old_path);
        exec_error_handler(fd[2], "cd", path, CD_DOES_NOT_EXIT_ERROR);
        return ;
    }
    set_env("OLDPWD",old_path, envp_list);
    path = getcwd(NULL,0);
    set_env("PWD",path, envp_list);
    if (is_minus)
        ft_putendl_fd(path, fd[1]);
    free(path);
}