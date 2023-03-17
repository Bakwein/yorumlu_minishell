/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateCmdTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:10 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:40:10 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_cmdtable(t_lexlist *lex_table)
{
	int		count;

	if (!lex_table) // lex_table boşsa
		return ;
	count = 1;
	while (lex_table) // lex_table dolu olduğu sürece ilerler
	{
		if (lex_table->type == SIGN_PIPE) // lex_table->type SIGN_PIPE ise
			count++;
		else if (lex_table->type != TEXT) // lex_table->type TEXT değilse(metachar?)
		{
			lex_table = lex_table->next; // lex_table'i bir sonraki elemana götürür.
			if (lex_table && lex_table->type == SIGN_PIPE) // lex_table doluysa ve lex_table->type SIGN_PIPE ise
				lex_table = lex_table->next; // lex_table'i bir sonraki elemana götürür.
			continue ;
		}
		lex_table = lex_table->next;
	}
	create_cmdtable_nodes(count);
}

void	fill_cmdtable_node(t_cmdlist *node) // default değerlerle node'u doldurur.
{
	node->pid = -1;
	node->infile = SSTDIN;
	node->outfile = SSTDOUT;
	node->cmd = NULL;
	node->path = NULL;
	node->next = NULL;
	node->files = NULL;
	node->heradoc_values = NULL;
}

void	create_cmdtable_nodes(int count)
{
	t_cmdlist	*temp_cmdtable;

	if (!count) // count 0 ise yani lex_tablo boşsa
		return ;
	g_core.cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	fill_cmdtable_node(g_core.cmd_table);
	temp_cmdtable = g_core.cmd_table; // temp_cmdtable g_core.cmd_table'ı gösterir.
	while ((--count)) // count 0 olana kadar azaltır.
	{
		temp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		fill_cmdtable_node(temp_cmdtable->next); // temp_cmdtable->next'i default değerler ile doldurur.
		temp_cmdtable = temp_cmdtable->next; // temp_cmdtable'i bir sonraki elemana götürür.
	}
}
