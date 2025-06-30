// 유효성검증을 해야한다 키에는 첫번째 문자로 숫자나 특수문자가 들어가면 안된다

//export key=value 일때 "key" "=" "value" 이렇게 온다 그렇다는건 strjoin으로 합쳐야겠네
// 인자가 =가 아닌 다른걸로 올때는 그냥 key만 입력되나
// "key" "=" "value" 이렇게 오니깐...
// 분류하자 다음에 =가 있냐없냐로
// =가 있다면 =의 그전거랑 다음거랑 합쳐버리고 그렇지않다면 그냥 key =' ' 이렇게 만들어버리고 오케이 일단 실행

// 케이스를 나누자면 export a=1 b=2 c 해버리면 a=1 b=2 c=' ' 가 되버리고
//  export a=c a= 해버리면 a=' '로 바뀜 그러니깐 그전에 한번 환경변수에서 찾아보고 넣어야할듯

// export a=1 b c d= a 해버리면
// 매개변수로 a = 1 b c d = a가 될거다
//  (1) i = 0; 
// argv[0] == '='이면 에러 메시지출력 후 종료
//  (2) a부터 시작 
//  (3) i++ 
//  (4) '=' 감지
//  (5) i-1,i,i+1 이렇게 합친다
//  (5-1) i+1이 NULL이면? -> 그냥 str[i+1]이 아닌 " "를 strjoin할때 해버린다
//  (6) i+1이 NULL이 아니여서 합쳐졌다면 i++을 두번해서 b로 이동한다
//  (7) b 다음 c기 때문에 b=' '로 한다
//  (8) i++
//  (9) c 다음은 d기 때문에 c=' '로 한다
//  (10) i++
//  (11) d 다음
// 치명적 문제 발생 ARG로 "a" "=" "1" "b" "c" "d" "=" "a"로 오기 때문에 d=' '가 아닌 d=a가 되버린다 지금 상황에선 이걸 해결할 방법이 없는것 같다

#include "builtin.h"

int ft_strcmp(char *str1, char* str2)
{
    int i;

    i = 0;
    while (str1[i] && (str1[i] == str2[i]))
        i++;
    return (str1[i] - str2[i]);
}

void sort_envp(char **envp)
{
    size_t len;
    size_t i;
    size_t j;
    char *tmp;

    i = 0;
    j = 0;
    len = ft_arglen(envp);
    while (i < len - 1)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (ft_strcmp(envp[j],envp[j + 1]) > 0)
            {
                tmp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}
char ** add_envp(char *arg)
{
    size_t i;
    size_t len;
    char **tmp_list;

    i = 0;
    len = ft_arglen(envp_list);
    tmp_list = malloc(sizeof(char *) * (len + 2));
    if (!envp_list)
        return (NULL);
    while (i < len)
    {
        tmp_list[i] = ft_strdup(envp_list[i]);
        i++;
    }
    tmp_list[len] = ft_strdup(arg);
    tmp_list[len + 1] = NULL;
    return (tmp_list);
}

void exec_export(int *fd, char **argv)
{
    char **tmp_list;
    int i;
    int j;

    j = 0;
    i = 0;
    tmp_list = get_envp_list(envp_list);
    if (argv[0][0] == '=')
    {
        exec_error_handler(fd[2], "export", NULL, EXPORT_DOSE_NOT_EQUAL);
        return ;
    }
    if (ft_arglen(argv) == 1) // 나중에 cmd로 올거 고려 고칠땐 0으로
    {
        sort_envp(tmp_list);
        while (tmp_list[j])
        {
            ft_putstr_fd("declare -x ",fd[1]);
            ft_putendl_fd(tmp_list[j],fd[1]);
            j++;
        }
    }
    else
    {
        tmp_list = add_envp(argv[1]);
        free_envp(envp_list);
        envp_list = tmp_list;
    }
}