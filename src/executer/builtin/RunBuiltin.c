/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunBuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:30:00 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:30:00 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (str_compare(cmd, "echo"))
		return (ECHO);
	else if (str_compare(cmd, "cd"))
		return (CD);
	else if (str_compare(cmd, "pwd"))
		return (PWD);
	else if (str_compare(cmd, "export"))
		return (EXPORT);
	else if (str_compare(cmd, "unset"))
		return (UNSET);
	else if (str_compare(cmd, "env"))
		return (ENV);
	else if (str_compare(cmd, "exit"))
		return (EXIT);
	return (0);
}

void	run_builtin(t_cmdlist *cmd_node, int builtin, int *fd, int fd_index)
{
	if (fd)
		create_dup(cmd_node, fd, fd_index);
	if (builtin == ECHO)
		run_echo(cmd_node);
	else if (builtin == CD)
		run_cd(cmd_node);
	else if (builtin == PWD)
		run_pwd(cmd_node);
	else if (builtin == EXPORT)
		run_export(cmd_node);
	else if (builtin == UNSET)
		run_unset(cmd_node);
	else if (builtin == ENV)
		run_env(cmd_node);
	else if (builtin == EXIT)
		run_exit(cmd_node);
}
