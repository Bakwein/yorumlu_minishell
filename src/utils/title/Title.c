/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:45:35 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:45:35 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	change_title(void)
{
	char	cwd[256]; // 256 byte yer ayırır
	char	*tmp; 
	char	*tmp2; 

	if (g_core.title.full_title) // eğer title doluysa
		free(g_core.title.full_title); // title'ı boşalt
	g_core.title.full_title = NULL; 
	tmp = ft_strtonl(g_core.title.head); // head'i newline'a göre ayırır.yani \n karakterini \0 yapar
	tmp2 = getcwd(cwd, 256); //getcwd ile cwd dizisine bulunduğu dizini atar
	own_strjoin1(&tmp, "-\033[0;32m[\033[0m");  // tmp'ye join
	if (tmp) // leak kontrolü
		free(tmp);
	if (str_compare(g_core.usrname, strrchr(tmp2, '/') + 1)) // eğer kullanıcı adı bulunduğu dizinin sonundaki klasör adıyla aynıysa(kök dizin) dosyanın konumu için ~ koyar
		own_strjoin1(&tmp, "~");
	else // değilse dosyanın konumunu yazdırır
		own_strjoin1(&tmp, strrchr(tmp2, '/') + 1);
	if (tmp) // leak kontrolü
		free(tmp);
	own_strjoin1(&tmp, "\033[0;32m]\n\033[0;36m└──\033[0;32m╼\033[0;36m$"); //tmp'ye join
	own_strjoin(&g_core.title.full_title, tmp); // full_title'e join
	own_strjoin(&g_core.title.full_title, "\033[0m"); //full_title'e join
	if (tmp) // leak kontrolü
		free(tmp);
}

/*
	burada her dongunun basinda yazilacak prompt olusturulur
	env'den expand edilerek yapilir.
*/
//	expand_envs(&g_core.title.head, "LOGNAME");
//	str_addchar(&g_core.title.head, '@');
//	expand_envs(&g_core.title.head, getenv("HOME"));
//	own_strjoin(&g_core.title.full_title, g_core.title.head);
//	own_strjoin(&g_core.title.full_title, "k2m10s07:~$ ");
///	own_strjoin(&g_core.title.full_title, g_core.title.head);
//	own_strjoin(&g_core.title.full_title, (char *)getcwd(cwd, 256));
//	own_strjoin(&g_core.title.full_title, "$ ");
/*void	set_title(void)
{
	g_core.title.head = NULL;
	g_core.title.full_title = NULL;
	own_strjoin(&g_core.title.head, "\033[0;36m▌│█║▌║▌║\033[0;32mᗰ ");
	own_strjoin(&g_core.title.head, TITLE);
	own_strjoin(&g_core.title.head, "\033[0;32m");
	own_strjoin(&g_core.title.full_title, g_core.title.head);
}*/
void	set_title(void)
{
	g_core.title.head = NULL; // baş kısım
	g_core.title.full_title = NULL; // değişen bölüm
	own_strjoin(&g_core.title.head, "\033[0;36m┌──\033[0;32m(\033[0;34m");// head'e joinler
	own_strjoin(&g_core.title.head, g_core.usrname); // head'e joinler
	own_strjoin(&g_core.title.head, "\033[0;32m@\033[0;34m" ); // head'e joinler 
	own_strjoin(&g_core.title.head, "minishell\033[0;32m)\n"); // head'e joinler 
	own_strjoin(&g_core.title.head, "\033[0;36m└──"); // head'e joinler
	own_strjoin(&g_core.title.head, "\033[0;32m╼\033[0;36m$"); // head'e joinler
	own_strjoin(&g_core.title.head, "\033[0m"); // head'e joinler
	own_strjoin(&g_core.title.full_title, g_core.title.head); // en son full title'a joinler
}
