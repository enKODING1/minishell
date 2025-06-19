# ifndef TOKEN_H
# define TOKEN_H

#include <stdlib.h>

// dollor sign도 토큰화 해야하나
typedef enum e_token {
    PIPE, // |
    HEREDOC, // << 
    APPEND, // >>
    OUT, // >
    IN, // <
    WORD, 
    END,
} t_token;

typedef struct s_token_type{
    t_token type;
    char * value;
} t_token_type;
# endif