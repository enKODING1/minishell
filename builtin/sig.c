#define _DEFAULT_SOURCE
#include "builtin.h"
#include <termios.h>
#include <readline/readline.h>

void sig_c()
{
    ft_putstr_fd("\n", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


void sig_back()
{
    write(1,"^\\",1);
}

void set_printf_off()
{
    struct termios term;

    tcgetattr(1, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(1, 0, &term);
}

void set_sig()
{
    set_printf_off();
    signal(SIGINT,sig_c);
    signal(SIGQUIT,sig_back);
}