/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:06:52 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 00:06:52 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>

typedef enum e_token
{
	PIPE,
	HEREDOC,
	APPEND,
	OUT,
	IN,
	WORD,
	END,
}			t_token;

typedef struct s_token_type
{
	t_token	type;
	char	*value;
}			t_token_type;
#endif
