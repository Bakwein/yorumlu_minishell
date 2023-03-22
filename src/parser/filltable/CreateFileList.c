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

	if (((*lex_list)->type) == TEXT) // lex_list'in tipi TEXT ise kalanlar zaten metacharlar oluyor
		return (0);
	meta = compare_metachars((*lex_list)->content);
	filename = NULL;
	if ((*lex_list)->next) // lex_list'in sonraki elemanı varsa
		filename = (*lex_list)->next->content; // filename metachardan sonraki elemanının içeriğine eşitlenir.
	if (*meta != *PIPE) // meta PIPE değilse
	{
		temp_filelist = add_filelist(&(node->files), filename, meta); // metachardan sonraki text'i filelist'e ekler
		temp_filelist->metachar = (*lex_list)->content; // metachar'ı alır
	}
	(*lex_list) = (*lex_list)->next; // metachardan sonraki listeye geçer
	if (*lex_list) // eğer metachardan sonraki liste NULL değilse ilerle
		(*lex_list) = (*lex_list)->next; 
	return (1);
}

t_filelist	*add_filelist(t_filelist **file_list, char *filename, char *meta) // birden fazla dosya kullanıldığında dosya isimleri burada tutulur.ls > c1.txt | ls | sort < dosya.txt gibi
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
	//ft_printf("\n%s**\n",temp_filelist->filename); girilen dosya isimlerini alır **c1.txt ve **dosya.txt basar
	temp_filelist->metachar = meta;
	temp_filelist->next = NULL;
	return (temp_filelist);
}
