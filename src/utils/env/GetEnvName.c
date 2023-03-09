/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetEnvName.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:43:28 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:43:28 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_env_name(char *content)
{
	int		env_name_len;
	char	*name;
	char	*temp_name;

	env_name_len = get_env_name_count(content); //env name(key) uzunluğu alınır
 	if (!env_name_len)  // 0'da null döndürülür
		return (NULL);
	name = (char *)malloc(sizeof(char) * (env_name_len + 1));
	temp_name = name; // adres 
	while (content && *content && *content != '=') // content ='e ulaşana kadar ilerler bunu dinamik olarak yer açtığmız temp_name'e yazar
		*(temp_name++) = *(content++);
	*temp_name = 0; //sona null
	return (name);
}

int	get_env_name_count(char *env_arg)
{
	int	count;

	count = 0;
	while (env_arg && *env_arg && *(env_arg++) != '=') // env null değilse ve = değilse ilerler uzunluğu döndürür
		count++;
	return (count);
}
