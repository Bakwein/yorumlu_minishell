/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UpdateLoop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:39:53 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:39:53 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_loop(void)
{
	g_core.old_exec_output = g_core.exec_output;
	g_core.exec_output = 0;
	g_core.is_read_arg = 0;
}
//	update_exec_output();

void	update_history(char *cmd)
{
	char	*ptr;

	if (!cmd) // bir şey alınmadıysa
		return ;
	ptr = cmd; 
	trim_spaces(&ptr); // komutun başındaki boşlukları atar
	if (!*ptr) // space'lerden arındırılmış komut boşsa
		return ;
	add_history(cmd); // komut history'e eklenir
}

void	update_exec_output(void)
{
	g_core.old_exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.old_exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.exec_output = 0;
}
