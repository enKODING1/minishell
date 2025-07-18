# minishell
[minishell.webm](https://github.com/user-attachments/assets/6f4c0fb4-187b-41a6-be24-96724dfc13ef)

# 설치
- Linux (o)
- macOS (x)
- Windows (x)

레포지토리 클론
``` bash
git clone https://github.com/enkoding1/minishell
```
make 명령어로 실행파일 생성
``` bash
make
```
minishell 실행
``` bash
./minishell
```

### lexer 테스터 설치
``` bash
make lexer
```
### parser 테스터 설치
``` bash
make parser
```
## **빌트인 명령어**
- [x] echo "-n" 옵션과 함께 구현
- [x] cd 상대경로, 절대경로 구현
- [x] pwd 옵션 구현 x
- [x] export 옵션 구현 x
- [x] unset 옵션 구현 x
- [x] env 옵션 구현 x
- [x] exit 옵션 구현 x

## **대화형 모드**
- [x] ctrl-C 새로운 프롬프트를 새 줄에 표시
- [x] ctrl-D 쉘 종료
- [x] ctrl-\ 아무것도 하지 않음

## **리다이렉션 구현**
- [x] < 입력 리다이렉션
- [x] > 출력 리다이렉션
- [x] << 구분기호를 넣는다, 구분기호가 나올 때 까지 입력을 읽는다, history는 저장하지 않음
- [x] >> 추가 모드에서 출력한다

# **파싱**
쉘 입력으로 들어오는 문자열을 의미 있는 토큰들로 구분 > 파서로 문법체크 > 실행 이 과정을 거쳐 작은 bash가 만들어진다. 파싱에 앞서 토큰들을 정의 해야한다.
### **토큰 정의**
``` BNF
typedef enum e_token{
	PIPE,     // |
	HEREDOC,  // <<
	APPEND,   // >>
	OUT,      // >
	IN,       // <
	WORD,     // cat, filename, string, number...
	END
}
```
크게 구분해야할 요소들은 PIPE, REDIRECTION(<, >, <<, >>), WORD, END 다. 각 요소들은 특정 문자가 왔을 때 뒤에 와야할 구문들이 각기 다른 요소를 기준으로 토큰화를 했다. 명령어, 명령어의 인자 를 별도의 cmd, cmd_args와 같은 토큰으로 분리하지 않고 모두 WORD토큰으로 취급하도록 했다. 파싱 단계에서 문법을 검사하며 유효하지 않는다면 에러를 발생시킬 거기 때문이다.

### **BNF 정의**
파싱 후 ast를 만들어야 하는데 이때 BNF(Backus–Naur form)표기법을 이용하면 트리를 어떻게 만들어야 할지와 문법적 구조를 간단하게 확인할 수 있다. 해당 규칙을 기반으로 파서는 현재 토큰들이 올바른 위치에 왔는지 확인하고 현재 토큰 다음에 출현해야할 토큰이 아니라면 문법적 오류를 출력해줄 수 있다.
``` c
<PIPE> ::= <COMMAND> [<COMMAND>"|"<PIPE>]
<COMMAND> ::= <COMMAND_ELEMENT>+
<COMMAND_ELEMENT> ::= <WORD> | <REDIRECTION>
<REDIRECTION> ::= ("<" | "<<" | ">" | ">>") <WORD>
```
가장위의 PIPE 부터 가장 아래의 요소까지 모두가 연결되어 문법 구조를 이룬다. 특정 토큰이 들어왔을 때 PIPE에 대응되는 함수를 호출 해 해당 특정 토큰이 있는 요소까지 내려가 검사를 하게 된다. 이 과정에서 현재 등장해야할 토큰이 아닌데 등장했다면 문법 오류를 뱉어내게 구현한다.

### **AST**
``` bash
<< eof << eof << eof cat | cat > outfile | cat > iutfile
```
```


            	[PIPE_NODE] (루트)
                 /           \
                /             \
        [CMD_NODE]             [CMD_NODE]
        /    \                   /   \
       /      \                 /     \
cmd: "cat"   [REDIR_NODE]      cmd: "cat" [REDIR_NODE]
args: (비어있음) |                        args: (비어있음) |
             [REDIR_NODE]                             type: OUT
             |                                        file: "outfile"
             [REDIR_NODE]
             |
             (세 개의 HEREDOC 노드가 연결 리스트로 연결됨)
             - type: HEREDOC, file: "eof"
             - type: HEREDOC, file: "eof"
             - type: HEREDOC, file: "eof"
```
``` bash
echo "hello world" > infile
```
```
      [CMD_NODE]  <-- 이 노드가 트리의 루트(Root).
      /        \
     /           \
cmd: "echo" |    [REDIR_NODE]
args: ["hello world"]    |
                      type: OUT
                      file: "infile"
```
### **parser**
parser는 현재 토큰을 기반으로 문법을 분석하고 문법이 틀리지 않았다면 노드를 생성해 ast를 만들어 가는 과정이다. BNF 구조에 따라 가장 위의 비단말 기호 부분부터 아래로 내려간다. 각 비단말 기호에 대응되는 parse 함수를 만든 후 bnf 의 규칙과 동일하게 구현한다.
### **parse redirection**
```c

t_redir *parse_redirs(t_parser *parser)
{
    t_redir *redir_head = (t_redir *)ft_calloc(1, sizeof(t_redir));

    redir_head->type = peek_token(parser)->type;
    consume_token(parser);

    if (!peek_token(parser) || peek_token(parser)->type != WORD)
    {
        parser->has_error = 1;
        free(redir_head);
        return NULL; 
    }

    redir_head->filename = peek_token(parser)->value;
    consume_token(parser);
    return redir_head;
}
```
### **parse command**
``` c
t_node *parse_cmd(t_parser *parser)
{
    t_cmd_node *cmd_head = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
    cmd_head->type = NODE_CMD;
    cmd_head->args = (char **)ft_calloc(20, sizeof(char *));

    int i = 0;
    while (peek_token(parser) && peek_token(parser)->type != PIPE && peek_token(parser)->type != END)
    {
        if (peek_token(parser)->type == WORD)
        {
           if (cmd_head->cmd == NULL) 
                cmd_head->cmd = peek_token(parser)->value;
			else 
                cmd_head->args[i++] = peek_token(parser)->value;
			consume_token(parser);
        }
        else if (peek_token(parser)->type >= HEREDOC && peek_token(parser)->type <= IN)
        {
            t_redir *redir = parse_redirs(parser);
            if (parser->has_error)
                return NULL;
            if (!cmd_head->redirs)
            {
                cmd_head->redirs = redir;
            }
            else
            {
                t_redir *current = cmd_head->redirs;
                while(current->next)
                    current = current->next;
                current->next = redir;
            }
        }
        else break;
    }
    return (t_node *)cmd_head;
}
```
### **parse pipe**
``` c
t_node *parse_pipe(t_parser *parser)
{
    if (!peek_token(parser) || peek_token(parser)->type == END) 
        return NULL;

    t_node *node = parse_cmd(parser);
	if (parser->has_error) 
        return NULL;

	if (peek_token(parser) && peek_token(parser)->type == PIPE)
	{
		consume_token(parser);
		if (!peek_token(parser) || peek_token(parser)->type == END) 
        { 
            parser->has_error = 1; 
            return NULL; 
        }
		t_pipe_node *pipe = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
		pipe->type = NODE_PIPE;
		pipe->left = node;
		pipe->right = parse_pipe(parser);
		if (parser->has_error) return NULL;
		return (t_node *)pipe;
	}
	return node;
}
```
### **executor (파이프)**
ast의 구조를 토대로 pipe를 만날 때 마다 자식 프로세스를 만들고 재귀를 통해 명령어를 실행한다. 이 방식의 장점은 생성된 ast그대로 순회를 하면 되기때문에 간단하다.

### **executor(리다이렉션)**
리다이렉션은 명령어 보다 우선 실행되어 파일 입출력 방향을 리다이렉션 해야한다. 그러므로 명령어 실행직전에 설정을 한다. builtin 명령어의 경우는 새로운 프로세스를 생성하게 되면 bash와 동작이 달라지므로 부모프로세스 자체에서 실행해야한다. redirection을 부모 프로세스에서 하게 되면 기존의 입/출력 리다이렉션을 백업 후, 명령어 실행이 끝나면 복원하는 방식으로 구현했다.

### **heredoc (bash 기준)**
<< limiter, 형식으로 터미널에 입력을 한다. heredoc만 입력시 별도의 출력은 없음. heredoc과 블로킹 명령어를 함께 사용하면 블로킹 명령어로 입력값이 들어간다. 키보드로 표준 입력을 받는다. 입력받은 문자열은 /tmp/ 내부에 파일을 생성해서 해당 파일에 데이터를 쓴다. heredoc의 limiter를 만나게 되면 임시 문자열 저장. 파일을 쓰기로 리다이렉션 한다. 그리고 unlink후 실행을 종료한다. 이렇게 구현하면 블로킹 명령어가 존재한다면 명령어의 표준입력으로 인해 값이 들어갈 것이고, 그렇지 않다면 출력되지 않을 것이다.


