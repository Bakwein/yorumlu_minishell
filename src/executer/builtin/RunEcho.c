/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunEcho.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:26 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:31:26 by stunca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_echo(t_cmdlist *cmd_node)
{
	char	**path;
	int		is_n;
	int		i;

	is_n = 0;
	i = 0;
	path = &cmd_node->path[1];
	if (path[i] && str_compare(path[i], "-n"))
	{
		is_n = 1;
		i++;
	}
	while (path[i])
	{
		if (path[i] && str_compare(path[i], "-n") != 1)
			write(cmd_node->outfile, path[i], ft_strlen(path[i]));
		if (path[i++] && path[i] && str_compare(path[i - 1], "-n") != 1)
			write(cmd_node->outfile, " ", 1);
	}
	if (!is_n)
		write(cmd_node->outfile, "\n", 1);
}
