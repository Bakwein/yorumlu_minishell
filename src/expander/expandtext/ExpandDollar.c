/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandDollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:06 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:36:06 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expand_dollar(char **dst, char **src)
{
	char	*ptr;

	ptr = (*src) + 1; // dolardan bir sonraki adres ptr'ye atanır
	if (*ptr == *DOLLAR) // eğer o da dolar ise girer => $$
		double_dollar(dst, src);
	else if (*ptr == *QUSTION_MARK) // eğer o  soru işareti ise girer => $?
		question_mark(dst, src);
	else if (*ptr == ' ' || !*ptr || *ptr == *DOUBLE_QUOTE
		|| *ptr == *SINGLE_QUOTE) // ilk dolardan sonra ' ',NULL," veya ' varsa
		single_dollar(dst);
	else
		expand_dollar_value(dst, src);
}

void	single_dollar(char **dst) 
{
	str_addchar(dst, *DOLLAR); // dst'ye $ ekler
}

void	double_dollar(char **dst, char **src) //$$ BU BOZUK MU KONTROL EDİLECEK
{
	char	*line;

	line = ft_itoa(g_core.old_exec_output); // old_exec_output int değerini stringe çevirir
	own_strjoin(dst, line);// dst'ye line'ı ekler
	free(line);
	(*src)++;
}

void	question_mark(char **dst, char **src) //$?
{
	char	*line;

	line = ft_itoa(g_core.old_exec_output); // old_exec_output int değerini stringe çevirir
	own_strjoin(dst, line);  // dst'ye line'ı ekler
	free(line);
	(*src)++;
}

void	expand_dollar_value(char **dst, char **src) // ENV ELEMANLARINI KONTROL ETMEK İÇİN
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = (*src) + 1; // $'dan sonraki adres atanır
	while (*ptr != ' ' && *(ptr) && *ptr != *DOUBLE_QUOTE
		&& *ptr != *SINGLE_QUOTE && *ptr != '$') // $'dan sonraki adres boşluk veya NULL veya " veya ' veya $ değilse count ve adres attırırlır
	{
		count++;
		ptr++;
	}
	ptr = ft_strpcpy(NULL, (*src) + 1, count); // NULL olan bir adrese $'dan sonraki adresi ve sonrasını count kadar kopyalar ardından bunu ptr'ye yazar
	expand_envs(dst, ptr); 
	free(ptr);
	*src += count; // src'yi count kadar ileri atar
}
