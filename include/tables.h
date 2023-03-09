/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:35 by stunca            #+#    #+#             */
/*   Updated: 2023/02/19 14:45:35 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLES_H
# define TABLES_H

typedef struct s_title
{
	char	*head;
	char	*full_title;
}	t_title;

typedef struct s_env
{
	char			*env_name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_lexlist
{
	char				type;
	char				*content;
	struct s_lexlist	*next;
}	t_lexlist;

typedef struct s_filelist
{
	char				*metachar;
	char				*filename;
	int					fd;
	struct s_filelist	*next;
}	t_filelist;

typedef struct s_cmdlist
{
	int					infile;
	int					outfile;
	int					pid;
	char				*heradoc_values;
	char				*cmd;
	char				**path;
	t_filelist			*files;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_core
{
	int			main_pid;
	int			exec_output;
	int			old_exec_output;
	int			heradoc_fd;
	int			is_read_arg;
	char		*usrname;
	char		*cmd;
	char		**metachars;
	t_env		*env_table;
	t_lexlist	*lex_table;
	t_cmdlist	*cmd_table;
	t_title		title;
}	t_core;

#endif
