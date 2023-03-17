/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandText.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:24 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:36:24 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expand_envs(char **dst, char *ptr) //ptr adında bir env key'i var mı kontrol eder. varsa contentini boş dst'ye joinler.
{
	t_env	*copy_envs;

	copy_envs = g_core.env_table; // env_table'ı copy_envs'e kopyalar
	while (copy_envs)
	{
		if (str_compare(ptr, copy_envs->env_name)) // ptr ile copy_envs->env_name aynı ise
 		{
			own_strjoin(dst, copy_envs->content); // dst'ye copy_envs->content ekler
			break ;
		}
		copy_envs = copy_envs->next;
	}
}

void	expand_order(char **dst, char **src)
{
	if (**src == *DOLLAR) // src $ ise
		expand_dollar(dst, src);
	else // src ~ ise
		expand_envs(dst, "HOME"); // üstteki fonksiyonu çağırır. HOME keyinin return değerini dst'ye ekler.
}
