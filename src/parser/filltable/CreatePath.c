/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreatePath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:30 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:40:30 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**create_path(t_lexlist *lex_list)
{
	int		count;
	char	**path;

	count = 0;
	while (lex_list && lex_list->type != SIGN_PIPE) // lex_listte pipe işareti gelene kadar veya lex_list NULL olana kadar ilerler
	{
		if (lex_list->type == TEXT && lex_list->content) // lex_list->type TEXT ve lex_list->content NULL değilse
			count++; // count arttırılır
		else // lex_list->type TEXT değilse veya lex_list->content boş ise
		{
			lex_list = lex_list->next; 
			if (lex_list) // lex_list NULL değilse
				lex_list = lex_list->next;
			continue ;
		}
		lex_list = lex_list->next;
	}
	if (!count) // count 0 ise
		return (NULL);
	path = (char **)malloc(sizeof(char *) * (count + 1)); // path için bellek ayırılır.
	path[count] = NULL; // path'in son elemanı NULL olur.
	return (path); // path döndürülür.
}
