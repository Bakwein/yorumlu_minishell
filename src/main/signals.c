/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:39:47 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:39:47 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handler(int signum)
{
	change_title();
	(void)signum; // kullanılmayan değişkenler için kullanılır.
	if (signal_in_reading()) //main pid değilse ve is_read_arg 1 ise direkt exit ile çıkar. main pid'ye eşit olup is_read_arg 1 ise buraya girer
		return ;
	if (signal_while_cmd_works())
		return ;
	g_core.exec_output = SIGNAL_C; // exec_output SIGNAL_C(130) ye eşitlenir.
	write(1, "\n", 1);
	free_for_loop(); // leak olmaması için freelemek
	rl_on_new_line(); //imleç konumunun satır başına dönmesini sağlar
	rl_replace_line("", 0); // ilk parametre olarak verilen boş dize ("") ile, mevcut satırın tamamen silindiği ve yerine boş bir satırın yazıldığı anlamına gelir. İkinci parametre olarak verilen 0, imlecin yeni satıra geçmeden önce mevcut satırda kalmasını sağlar.
	rl_redisplay(); //  kullanıcının girdi tamponunda yapacağı değişiklikleri yeniden görüntülemesine izin verir.(?)
}

int	signal_in_reading(void)
{
	ft_printf("%d - %d\n",g_core.is_read_arg, g_core.pid);
	if (g_core.is_read_arg && g_core.pid == 0) // alınan pid main pid değilse ve is_read_arg 1 ilse girer
	{
		free_for_loop(); // alttaki ile beraber leak önlemek için free fonksiyonuları
		free_core();
		exit(SIGNAL_C); // exit fonksiyonu ile çıkış yapılır.(SIGNAL_C = 32)
	}
	else if (g_core.is_read_arg && g_core.pid !=0) // main pid ise ve is_read_arg 1 ise
	{
		g_core.exec_output = SIGNAL_C; // exec_output SIGNAL_C(130) ye eşitlenir.
		return (1);
	}
	return (0);
}

int	signal_while_cmd_works(void)
{
	t_cmdlist	*cmd_list;
	int			return_value;

	return_value = 0;
	cmd_list = g_core.cmd_table; // cmd_table'ı cmd_list'e atar.
	while (cmd_list) 
	{
		if (cmd_list->pid >= 0) // pid 0 dan büyükse
			return_value |= waitpid(cmd_list->pid, 0, 0);  // return_value = return_value | waitpid(cmd_list->pid, 0, 0); işlemi yapar. sadece 2si 0 olduğunda 0 aksi takdirde 1 döndürür.
		cmd_list = cmd_list->next;
	}
	if (return_value) // return_value 1 ise 
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void	exit_signal_check(void)
{
	if (!g_core.cmd) 
	{
		write(1, "Exit\n", 6);
		free_core();
		exit(EXIT_SUCCESS);
	}
}
