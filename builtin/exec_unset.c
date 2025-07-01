// unset 아무것도 안했을때 그냥 아무것도 안하고 종료코드 1 반환
// unset 첫번째 글자에 숫자나 특수문자가 들어오면 unset: 1a: invalid parameter name 이렇게 출력
// unset 인자 여러개가 들어와도 다 처리한다 다만 유효성 검사를 인자마다 진행
// unset이나 모든 명령어가 unset \이런식으로 백슬래시가 온다면 표준 입력이 열려야한다
// c2r19s6% unset `
//  bquote> 이렇게 열린다  
#include "builtin.h"

static int ft_check(char *str)
{
    int i;

    i = 1;
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    while (str[i])
    {
        if (!(ft_isalnum(str[i]) ||str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

static void ft_pull(int i, char **envp_list)
{
    free(envp_list[i]);
    while (envp_list[i])
    {
        envp_list[i] = envp_list[i + 1];
        i++;
    }
}

void exec_unset(int *fd, char **argv)
{
    size_t key_len;
    int i;
    int j;

    i = 0;
    fd[2] +=1;
    while (argv[i])
    {
        j = 0;
        if (!ft_check(argv[i]))
            continue; // bash에선 에러메시지 발생안해서 이랬는데 에러메시지를 출력하는게 맞는건가...
        key_len = ft_strlen(argv[i]);
        while (envp_list[j])
        {
            if (ft_strncmp(argv[i],envp_list[j],key_len) == 0 && envp_list[j][key_len] == '=')
            {
                ft_pull(j,envp_list);
                continue;
            }
            j++;
        }
        i++;
    }
}
