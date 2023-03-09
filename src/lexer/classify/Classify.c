/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:59 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:36:59 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/*
	olusturulmus lexer bagli listesinde ki her nodeda bulunan 
	sozcuklerin tipi belirlenir.
	bu olusturulan tiplerin karsiliklari "lexer.h"'da define edilmistir
	oradan karsiliklari gorulebilir ve kontrol islemleri
	orda define edilmis degiskenler uzerinden yapilabilir.
*/

void	classify(t_lexlist *lex_table)
{
	char	*metachars;

	if (!lex_table) // lexer bagli listesi bos ise
		return ;
	while (lex_table) 
	{
		metachars = compare_metachars(lex_table->content); // her bir node icin metachar dizisi ile karsilastirilir
		if (metachars) // eger metachar varsa
			lex_table->type = (*metachars) * ft_strlen(metachars); // 1 ve 2 uzunlukta olan metacharlar icin uzunluk 1 ise 1 , 2 ise 2 ile metachar'in ilk elemaninin(<,>,|) ascii değeri çarpılır. Bu sonuç bizim define ile tanımladığımız tiplerin değerlerine eşittir.o değerleri ise node'un tipine atarız
		else // metachar yoksa
			lex_table->type = 0; // text olarak atarız
		lex_table = lex_table->next;
	}
}
