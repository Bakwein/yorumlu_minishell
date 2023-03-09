/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintError.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:43:41 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:43:41 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	print_lex_error(t_lexlist *lex_list)
{
	print_error("-bash: syntax error near unexpected token '",
		lex_list->content, "'\n"); // hata mesaji
	g_core.exec_output = 2; // 2: syntax error
	free_lexer_without_heradoc(lex_list); // hata varsa bagil listeyi sil
	return (0);
}

void	print_error(char *ptr1, char *ptr2, char *ptr3)
{
	write(2, "\033[0;31m", 7);
	if (ptr1) // hata mesaji
		write(2, ptr1, ft_strlen(ptr1));
	if (ptr2) // hata mesaji
		write(2, ptr2, ft_strlen(ptr2));
	if (ptr3) // hata mesaji
		write(2, ptr3, ft_strlen(ptr3));
	write(2, "\033[0;32m", 7);
}
