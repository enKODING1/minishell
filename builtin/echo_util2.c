/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:34:50 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:41:18 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_single_quote(char **str, t_string_builder *list)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		append_char(list, **str);
		(*str)++;
	}
	if (!**str)
	{
		exec_error_handler(STDERR_FILENO, "syntax error", NULL,
			"unclosed quote");
		return (1);
	}
	(*str)++;
	return (0);
}

int	handle_double_quote(char **str, char **envp_list, t_string_builder *list)
{
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$')
			*str += expand_env(*str + 1, envp_list, list);
		else
			append_char(list, **str);
		(*str)++;
	}
	if (!**str)
	{
		exec_error_handler(STDERR_FILENO, "syntax error", NULL,
			"unclosed double quote");
		return (1);
	}
	(*str)++;
	return (0);
}
