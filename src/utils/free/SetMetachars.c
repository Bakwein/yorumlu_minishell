/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetMetachars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:43:59 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:43:59 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	global degiskende ki metachars degiskenine 2 boyutlu bir dizi olusturur
	ve icerisine teker teker belirlenen metakarakterleri atar.
	metakarakterler sirasiyla ">>", "<<", "<", ">", "|"'dir
*/
void	set_metachars(void)
{
	char	**meta_list;

	meta_list = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1)); // 5 + 1(NULL)
	g_core.metachars = meta_list; //global değişken elemanına adres adama
	*(meta_list++) = ft_strdup(DOUBLE_GREAT); // >>
	*(meta_list++) = ft_strdup(DOUBLE_LESS); // <<
	*(meta_list++) = ft_strdup(SINGLE_LESS); // < 
	*(meta_list++) = ft_strdup(SINGLE_GREAT); // >
	*(meta_list++) = ft_strdup(PIPE); // |
	*(meta_list++) = NULL; // sona null
}
