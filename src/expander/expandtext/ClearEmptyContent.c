/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClearEmptyContent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:35:57 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:35:57 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	clear_void_contents(void) // ptr ile atanmış lexlist'teki boş contentleri temizler. after_meta'da zaten sıfırlanmayacağından bu text'lerde oluşanlar için sanırım
{
	t_lexlist	*lex_list;
	t_lexlist	*temp_lex_list;

	lex_list = g_core.lex_table;
	temp_lex_list = g_core.lex_table;
	while (lex_list)
	{
		if (!lex_list->content) // lexlist'in contenti yoksa
		{
			if (lex_list == g_core.lex_table) // lexlist'in ilk elemanı ise
			{
				g_core.lex_table = g_core.lex_table->next; // lexlist'in ilk elemanını siler. next'i asıl adresi olur.
				temp_lex_list = temp_lex_list->next; 
			}
			else // lexlist'in ilk elemanı değilse
				temp_lex_list->next = lex_list->next; // TEMP'in gösterdiği boş contenti olanın öncesinde olduğundan lex_list zaten şu an boş contenti gösterdiğinden next'i temp'in next'ine atanarak ortadaki boş eleman ile ilişki kesilir. temp_lex_list'in next'i lexlist'in next'i olur.
			free(lex_list); // lexlist'i siler.
			lex_list = temp_lex_list; // lexlist temp_lex_list'e eşitlenir. böylece ortaki boş elemanı atlamış olur.
		}
		temp_lex_list = lex_list; // temp_lex_list lexlist'e eşitlenir.
		if (lex_list) // lexlist varsa
			lex_list = lex_list->next;
	}
}
