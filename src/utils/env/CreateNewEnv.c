/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateNewEnv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:43:18 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:43:18 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	mainde 3.parametre olarak aldığımız env değişkenini alır
	ve bağlı liste yapısına doldurur.
*/
void	fill_envs(char **env)
{
	while (env && *env) //envde sona kadar ilerlendi hepsi birer listeye eklendi
		add_newenv(&g_core.env_table, *(env++)); //globalde tutulan tablo adresi, env adresi teker teker arttırılır
}

/*
	bağlı liste yapısında henüz bir bode yok is onu yaratır
	var is sonuna gider ve ardına yeni bir node ekler.
	Gelen parametreyi oraya ekler.
*/
t_env	*add_newenv(t_env **env_table, char *env)
{
	t_env	*last_node;
	char	*content;

	if (!*env_table) //oluşturulacak liste boşsa girer
	{
		*env_table = (t_env *)malloc(sizeof(t_env));
		last_node = *env_table;
	}
	else
	{
		last_node = *env_table;
		while (last_node->next) // listedeki son elemana kadar ilerlenir
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env));
		last_node = last_node->next;
	}
	last_node->env_name = get_env_name(env); //env name alınması için env adresi(fonksiyona şu an kullanacağımız env adresi yollandı!) gönderilir
	content = env + ft_strlen(last_node->env_name); //fonksiyon ile alınan env adresine env uzunluğu eklenir ve varsa ='e ulaşılır
	if (*content == '=' && *(content + 1)) // ulaşılan değer = ise ve ='den sonra bir şeyler varsa girer
		last_node->content = ft_strdup(content + 1); // ='den sonraki adrese strdup yapılır(dinamik olarak yer açılır)
	else
		last_node->content = NULL; // =  değilse content'e(value) NULL atanır
	last_node->next = NULL; 
	return (last_node); // oluşturulan liste elemanın adresi döndürülür
}

char	*get_env(char *env_name)
{
	t_env	*temp_env;

	temp_env = g_core.env_table;
	while (temp_env)
	{
		if (str_compare(env_name, temp_env->env_name))
			return (temp_env->content);
		temp_env = temp_env->next;
	}
	return (NULL);
}
