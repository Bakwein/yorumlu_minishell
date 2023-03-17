/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandLexList.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:15 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:36:15 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expand_values_from_lexlist(void)
{
	t_lexlist	*lex_table;

	lex_table = g_core.lex_table;
	while (lex_table) // lex table elemanlarının sonuna kadar ilerleyecek
	{
		if (lex_table->type == TEXT) // lex_table elemanı text ise
			expand_text(lex_table, 0);
		else if (lex_table->next && lex_table->type != SIGN_PIPE) // lex_table next'i varsa ve lex_table type'ı pipe değilse
		{
			if (lex_table->type != SIGN_DOUBLE_LESS) // lex_table type'ı double less değilse
				expand_text(lex_table->next, 1); // mesela > "$TERM_PROGRAM" verildiğinde vscode adında bir dosya yaradır önckei mantık gibi " varsa content, ' varsa ismi kullanarak metachar ne işe yarıyorsa onu yapar. 
			lex_table = lex_table->next;
		}
		lex_table = lex_table->next;
	}
}

void	expand_text(t_lexlist *lex_table, int is_after_meta)
{
	char	*cmd;
	int		flag;
	char	*ptr; // eğer lex_table elemanının content'i değiştirilmek istenirse kullanılmak için en son kısımda ptr'yi lex_table->content'e atar.

	cmd = lex_table->content; // lex_table contentini cmd'ye atar.
	ptr = NULL; 
	flag = 0;
	while (*cmd) // cmd sonuna kadar ilerleyecek
	{
		if (*cmd == '\'' && (!flag || flag == 1)) // cmd ' ise ve flag 0 veya 1 ise
			flag = flag ^ 1; // flag 1 ise 0'a eşitlenir, flag 0 ise 1'e eşitlenir.
		else if (*cmd == '\"' && (!flag || flag == 2)) // cmd " ise ve flag 0 veya 2 ise
			flag = flag ^ 2; // flag 0 ise 2'ye eşitlenir, flag 2 ise 0'a eşitlenir.
		else if ((!flag || flag == 2) && (*cmd == *DOLLAR || *cmd == *TILDA)) // flag 0 veya 2 ise ve cmd $ veya ~ ise
			expand_order(&ptr, &cmd); // " için
		else
			str_addchar(&ptr, *cmd); // ptr'ye cmd'yi ekler. ' için
		cmd++;
	}
	if (is_after_meta && !ptr) // is_after_meta 1 ise ve ptr NULL ise
		return ; // metadan sonra üst kısımda ptr'ye herhangi bir return değeri atanmamışsa freelemeden ve ptr'ye atanmadan çık.NEDENİ sanırım contenti sıfırlamak istememek.????????????????????????????
	free(lex_table->content);
	lex_table->content = ptr; // lex_table contenti değişir, ptr'ye eşitlenir.
}

/*
echo "$HOME" HOME'ın contenini, echo '$HOME' HOME'ı yazdırır.!!!
*/