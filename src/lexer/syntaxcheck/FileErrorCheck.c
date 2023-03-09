/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:38:19 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:38:19 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	file_error_check(t_lexlist *lex_list)
{
	if (!lex_list->next || (lex_list->next && lex_list->next->type != TEXT)) // eger bir sonraki eleman yoksa veya bir sonraki eleman text değilse (EMİN DEĞİLİM AMA SANIRIM <<,>>,<,> 'den sonra kesinlikle text gelmeli yoksa hata!)
	{
		if (lex_list->next) 
		{
			print_error("-bash: syntax error near unexpected token '",
				lex_list->next->content, "'\n"); // hata mesaji
			g_core.exec_output = 2; // hata kodu syntax error
			free_lexer_without_heradoc(lex_list); // hata varsa bagil listeyi sil
			return (0);
		}
		else
		{
			print_error("-bash: syntax error near unexpected token '",
				"newline", "'\n"); // hata mesaji
			g_core.exec_output = 2; // hata kodu syntax error
			free_lexer_without_heradoc(lex_list); // hata varsa bagil listeyi sil
			return (0);
		}
	}
	return (1);
}
