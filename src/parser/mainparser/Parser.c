/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:56 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:40:56 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	parser(void)
{
	g_core.cmd_table = NULL; // komut tablosunu NULL yapar.
	create_cmdtable(g_core.lex_table); // cmdtable oluşturur.
	fill_cmdtable(); //CMD_TABLE'ı doldurur.
	create_files(g_core.cmd_table);
}
