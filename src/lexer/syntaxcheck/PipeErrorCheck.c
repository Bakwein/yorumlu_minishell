/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:38:40 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:38:40 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	pipe_error_check(t_lexlist *lex_list)
{
	if (lex_list->next && lex_list->next->type == SIGN_PIPE) // pipe ardından pipe ise
		return (print_lex_error(lex_list)); // 0 döndürür
	else if (!lex_list->next) // pipe son eleman ise
		return (run_miss_arg(lex_list)); // eksik argümanı al
	return (1);
}
int	run_miss_arg(t_lexlist *lex_list)
{
	char	*ptr;

	ptr = get_missing_arg(); // eksik argümanı al
	if (!ptr)
		return (1);
	create_lexlist(ptr, &lex_list); // yeni lexlist elemanı oluştur
	classify(lex_list); // yeni lexlist elemanını sınıflandır
	str_addchar(&g_core.cmd, ' '); // cmd'nin sonuna ' ' karakterini ekler.bir boşluk atar
	own_strjoin(&g_core.cmd, ptr); // cmd'nin sonuna ptr'yi ekler
	free(ptr); //ptr'i free eder
	if (str_compare(lex_list->next->content, PIPE)) // next'de pipe varsa. yani pipe girilmişse
		return (-1);
	return (1); // sorun yoksa 1 döner
}
