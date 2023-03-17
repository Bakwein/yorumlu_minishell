/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateFileList.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:20 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:40:20 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	create_new_filelist(t_cmdlist *node, t_lexlist **lex_list)
{
	char		*meta;
	char		*filename;
	t_filelist	*temp_filelist;

	if (((*lex_list)->type) == TEXT) // lex_list'in tipi TEXT ise
		return (0);
	meta = compare_metachars((*lex_list)->content);
	filename = NULL;
	if ((*lex_list)->next) // lex_list'in sonraki elemanı varsa
		filename = (*lex_list)->next->content; // filename lex_list'in sonraki elemanının içeriğine eşitlenir.
	if (*meta != *PIPE) // meta PIPE değilse
	{
		temp_filelist = add_filelist(&(node->files), filename, meta); // >> sefa tunca yazıldığında sadece sefa adında bir dosya oluşturur.
		temp_filelist->metachar = (*lex_list)->content; // temp_filelist'in metachar'ı lex_list'in içeriğine eşitlenir.
	}
	(*lex_list) = (*lex_list)->next;
	if (*lex_list) // lex_list NULL değilse
		(*lex_list) = (*lex_list)->next; 
	return (1);
}

t_filelist	*add_filelist(t_filelist **file_list, char *filename, char *meta)
{
	t_filelist	*temp_filelist;

	if (!*file_list) // file_list NULL ise
	{
		*file_list = (t_filelist *)malloc(sizeof(t_filelist));
		temp_filelist = *file_list;
	}
	else // file_list NULL değilse
	{
		temp_filelist = *file_list;
		while (temp_filelist->next) // sona kadar ilerler
			temp_filelist = temp_filelist->next;
		temp_filelist->next = (t_filelist *)malloc(sizeof(t_filelist));
		temp_filelist = temp_filelist->next;
	}
	temp_filelist->fd = 0;
	temp_filelist->filename = filename;
	temp_filelist->metachar = meta;
	temp_filelist->next = NULL;
	return (temp_filelist);
}
