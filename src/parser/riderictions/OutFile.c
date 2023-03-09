/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OutFile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:42:39 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:42:39 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_outfile(t_cmdlist *node, t_filelist *file)
{
	char	*outfile_path;
	char	ptr[256];

	if (raise_file_error(file, &node->outfile))
		return ;
	outfile_path = NULL;
	own_strjoin(&outfile_path, (char *)getcwd(ptr, 256));
	str_addchar(&outfile_path, '/');
	own_strjoin(&outfile_path, file->filename);
	if (file->metachar[1] == DOUBLE_GREAT[1])
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	node->outfile = file->fd;
	free(outfile_path);
}
