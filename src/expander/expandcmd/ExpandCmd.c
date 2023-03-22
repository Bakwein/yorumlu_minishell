/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandCmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:35:41 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:35:41 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expand_cmd(char **dst)
{
	t_env	*temp_env;

	temp_env = g_core.env_table;
	while (temp_env && *dst && **dst)
	{
		if (str_compare("PATH", temp_env->env_name)) // PATH ENV'sine kadar ilerler
		{
			expand_from_env_value(dst, temp_env->content); 
			return ;
		}
		temp_env = temp_env->next;
	}
}

void	expand_from_env_value(char **dst, char *content) //(lex_list->content, PATH ENV'sinin contenti->/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki)
{
	char	*control_ptr;

	while (content && *content)
	{
		control_ptr = get_arg_from_env_value(&content, *dst); //(/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki,lex_list->content) CONTENT ALTTAKİ KISIMDA ENVS OLARAK İLERLETİLDİĞİNDEN DOLAYI MESELA ECHO'YU İLK /usr/local/bin sonra /usr/bin sonra /bin döndürür.
		if (!access(control_ptr, F_OK)) // eğer dönen değer eğer dizinde varsa (/usr olduğunda) girer
		{
			ft_printf("girdi mi\n");
			free(*dst); 
			*dst = control_ptr; // lex_list->content = /usr/local/bin/echo
			return ;
		}
		free(control_ptr);//accesde sorun yoksa her seferinde freeler
	}
}

char	*get_arg_from_env_value(char **envs, char *search_arg_name)
{
	char	*ptr;
	int		count;
	char	*temp_envs;

	count = 0;
	temp_envs = *envs;
	while (*temp_envs && *temp_envs != ':') // PATH ENV'sinin contentindeki ':' karakterine kadar ilerler
	{
		count++;
		temp_envs++;
		(*envs)++;
	}
	if (!count) // count 0 ise
		return (NULL);
	if (**envs) //eğer PATH ENV'sinin contentindeki ':' karakteri varsa bir sonraki adrese geç.
		(*envs)++; 
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	ptr[count] = 0;
	while (--count > -1)
		ptr[count] = *(--temp_envs); // temp_Env içindeki değerler ptr içine atılır.
	//ft_printf("%s**\n",ptr); MESELA ECHO'YU İLK /usr/local/bin sonra /usr/bin sonra /bin döndürür.
	str_addchar(&ptr, '/'); // sonuna / eklenir
	own_strjoin(&ptr, search_arg_name); // ptr ile lex_list->content birleştirilir.
	return (ptr);
}
