/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunPwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:50 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:31:50 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_pwd(t_cmdlist *cmd_node)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(cmd_node->outfile, pwd, ft_strlen(pwd));
	write(cmd_node->outfile, "\n", 1);
}
