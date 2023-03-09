/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TrimSpace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:45:28 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:45:28 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	Gelen komutu bosluk gordukce adres uzerinde arttirir
	boylece geldigi fonksiyonda da artmis olur.
*/
size_t	trim_spaces(char **cmd_line)
{
	size_t	count;

	count = 0;
	if (!*cmd_line)
		return (count);
	while (**cmd_line == 32)
	{
		count++;
		(*cmd_line)++;
	}
	return (count);
}
