/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SynaxCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:38:51 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:38:51 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	syntax_check(void)
{
	t_lexlist	*lex_list;
	int			syntax_error;

	lex_list = g_core.lex_table; // ayrılmış komutların bulunduğu bagil liste
	while (lex_list)
	{
		syntax_error = syntax_error_check(lex_list);
		if (syntax_error == -1) // hata varsa
			break ;
		else if (!syntax_error) // sonda | yaptıktan sonra açılan bölümde tekrar sonuna | yaparsak sonusz döngü gibi devam edebilmesi için
			continue ;
		if (g_core.lex_table) // yeni eleman eklendiyse ayar çekilir
			lex_list = lex_list->next;
		else
			lex_list = NULL;
	}
}

int	syntax_error_check(t_lexlist *lex_list)
{
	int	pipe_error;

	if (lex_list == g_core.lex_table && lex_list->type == SIGN_PIPE) // ilk eleman pipe ise
	{
		print_lex_error(lex_list); // hata mesaji fonksiyonu
		return (-1);
	}
	else if (lex_list->type != TEXT && lex_list->type != SIGN_PIPE) // tip pipe veya text değilse(<,>,>>,<<)
	{
		if (!file_error_check(lex_list)) // 0 dönerse hata var
			return (-1);
	}
	else if (lex_list->type == SIGN_PIPE) // pipe ise
	{
		pipe_error = pipe_error_check(lex_list);
		if (pipe_error < 0) // | | | gibi bir durumda -1 döner
			return (0);
		else if (!pipe_error) // pipe_error NULL dönerse -breakler
			return (-1);
	}
	return (1);
}
