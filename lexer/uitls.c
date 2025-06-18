#include "lexer.h"

const char * token_type_str(t_token type){
    if (type == PIPE)
        return "PIPE";
    if (type == HEREDOC)
        return "HEREDOC";
    if (type == APPEND)
        return "APPEND";
    if (type == OUT)
        return "OUT";
    if (type == IN)
        return "IN";
    if (type == WORD)
        return "WORD";
    if (type == END)
        return "END";
    return NULL;
}