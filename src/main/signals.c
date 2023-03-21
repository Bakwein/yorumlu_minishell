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
	rl_on_new_line(); 
	rl_replace_line("", 0); 
	rl_redisplay(); 
}
/*
rl_on_new_line(): Bu fonksiyon, kullanıcının mevcut satırın sonuna geldiğini ve yeni bir satıra geçtiğini belirtmek için kullanılır. Yani, mevcut satırın sonunda bir '\n' karakteri varmış gibi hareket eder.
rl_replace_line("", 0): Bu fonksiyon, mevcut satırı tamamen siler ve yerine boş bir satır ekler. İkinci parametre, mevcut satırın uzunluğunu belirtir. Bu örnekte, 0 olarak belirtilmiştir, bu da mevcut satırın uzunluğunu bilmediğimizi ve tamamen silmek istediğimizi gösterir.
rl_redisplay(): Bu fonksiyon, kullanıcıya gösterilen satırı yeniler. Bu, mevcut satırın içeriğinde yapılan değişikliklerin hemen görünür hale gelmesini sağlar.
*/

int	signal_in_reading(void)
{
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
	if (return_value) // return_value 1 ise(EMİN DEĞİLİM AMA EĞER ÜSTTEKİ IF'E CHILD HARİCİ DEĞER GELDİĞİ DURUMDA BURAYA GİRER)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
/*
waitpid fonksiyonu, bir çocuk işlemi için ana işlemin beklemesini sağlar ve işlemin durumunu rapor eder.
pid_t waitpid(pid_t pid, int *status, int options);
status: Çocuk işlemin bitiş durumunu tutacak bir tamsayı göstericisi. Bu gösterici, çocuk işlem için rapor edilen çıkış kodunu ve diğer bilgileri içerir.
options: Bekleme davranışını kontrol eden bir bit haritası. Bu parametre, farklı bayrakların birleştirilmesiyle oluşturulabilir.

waitpid fonksiyonu, başarı durumunda çocuk işlemin PID'sini döndürür. Eğer bekleyen çocuk işlem yoksa veya hata oluşursa -1 döndürür ve errno değişkenine uygun hata kodunu yerleştirir.
*/
void	exit_signal_check(void)
{
	if (!g_core.cmd) 
	{
		write(1, "Exit\n", 6);
		free_core();
		exit(EXIT_SUCCESS);
	}
}
