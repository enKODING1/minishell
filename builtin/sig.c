#include "builtin.h"
void sig_c()
{
    write(1,"\n",1);
}


void sig_back()
{
    write(1,"^\\",1);
}

void set_sig()
{
    signal(SIGINT,sig_c);
    signal(SIGQUIT,sig_back);
}

// int main()
// {
//     set_sig();
// }