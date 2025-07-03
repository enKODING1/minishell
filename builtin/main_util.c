/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:04:37 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/03 17:05:24 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*shell_lv_up(char **envp_list)
{
	char	*target;
	char	*lv_str;
	int		level;

	target = search_envp("SHLVL", envp_list);
	level = ft_atoi(target);
	level++;
	lv_str = ft_itoa(level);
	target = ft_strjoin("SHLVL=", lv_str);
	free(lv_str);
	return (target);
}
