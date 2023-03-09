/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunEnv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:39 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:31:39 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_env(t_cmdlist *cmd_node)
{
	t_env	*temp_env;

	temp_env = g_core.env_table;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(cmd_node->outfile, temp_env->env_name,
				ft_strlen(temp_env->env_name));
			write(cmd_node->outfile, "=", 1);
			write(cmd_node->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(cmd_node->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
	}
}
