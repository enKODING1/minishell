/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:52:04 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/02 20:53:37 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <termios.h>
#include <readline/readline.h>

void	sig_c(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_back(int sig)
{
	(void) sig;
}

void	set_printf_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	set_sig(void)
{
	set_printf_off();
	signal(SIGINT, sig_c);
	signal(SIGQUIT, sig_back);
}
