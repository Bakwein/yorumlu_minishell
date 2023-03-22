/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FillCmdTable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:37 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:40:37 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	fill_cmdtable(void)
{
	t_cmdlist	*temp_cmdtable;
	t_lexlist	*temp_lexlist;

	if (!g_core.cmd_table) // komut tablosu yoksa
		return ;
	temp_cmdtable = g_core.cmd_table;
	temp_lexlist = g_core.lex_table;
	while (temp_cmdtable) // cmd tablosu sonuna kadar ilerler
	{
		fill_cmdnode(temp_cmdtable, &temp_lexlist);
		if (temp_lexlist && *temp_lexlist->content == *PIPE) // lex_list'lerdeki PIPE'ları atlamak için
			temp_lexlist = temp_lexlist->next; // LEX LIST İLERLER
		temp_cmdtable = temp_cmdtable->next; // CMD TABLE İLERLER
	}
}

void	fill_cmdnode(t_cmdlist *node, t_lexlist **lex_list)
{
	char	**path_holder;
	int		is_begin;

	node->path = create_path(*lex_list);
	path_holder = node->path; // path_holder node->path'in adresini tutar.
	is_begin = 0;
	while (*lex_list && (*lex_list)->type != SIGN_PIPE) // lex'listte pipe görene kadar ilerleyecek
	{
		if (create_new_filelist(node, lex_list)) // dosya listesi oluşturulur.
			continue ;
		if (!(is_begin++) && (*lex_list)->content) // sadece başlangıçta girer.is_begin 0 ise ve lex_list->content NULL değilse
			expand_cmd(&((*lex_list)->content)); //lex_list->content'ine PATH env değişkeninin içeriğini ekler. NEDEN?
		if ((*lex_list)->content) // lex_list->content NULL değilse
			*(path_holder++) = (*lex_list)->content; // üstteki işlemde yapılan olaylardan sonra tüm contentler pathleri tutar.o contentlerin adreslerini sırasıyla path_holder'a atar.
		*lex_list = (*lex_list)->next;
	}
	//ft_printf("%c\n",node->path[0]); BURADA ÇIKAN SONUÇ mesela echo "sefa"| pwd olursa node->path[0] = echo'nun path'i yani /bin/echo ve diğer listede pwd'nin path'i yani /bin/pwd olur.ilk baştaki cmd_list'in path[1]'i ise sefa olur.
	if (node->path) // node->path NULL değilse
		node->cmd = node->path[0]; // node->cmd node->path'in ilk elemanını gösterir.
}
