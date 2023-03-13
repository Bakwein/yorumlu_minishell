/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:38 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:36:38 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expander(void)
{
	if (g_core.exec_output == 2) // eğer exec_output 2 ise(hata kodu-syntax error olması lazım)
		return ;				 // diğerlerine girer mi BAK!
	expand_values_from_lexlist();
	clear_void_contents();
}
