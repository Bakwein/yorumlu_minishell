/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:39:23 by hsozan            #+#    #+#             */
/*   Updated: 2023/03/14 14:08:09 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_core	g_core; //global

int	main(int argc, char **argv, char **env)
{
	(void)argc; // kullanılmayan değişkenler için kullanılır.
	(void)argv; // kullanılmayan değişkenler için kullanılır.
	init_core(env); // init core'a env'i gönderiyoruz.
	signal(SIGINT, &sig_handler); // ctrl+c sinyali için signalfonksiyonu kullanılır.
	while (1)
	{
		update_loop();
		g_core.cmd = readline(g_core.title.full_title); // yazdığımız şeyi cmd'ye atar.
		exit_signal_check(); // ctrl+d sinyali için signalfonksiyonu kullanılır.BUNU NASIL ALGILIYOR??????
		lexer(); // komutu parçalara ayırır.
		expander(); 
		parser(); // komutu parse eder.
		executer(); // komutu çalıştırır.
		update_history(g_core.cmd); // komutu history'e ekler.
		free_for_loop(); // döngüyü freeler
	}
	free_core(); // Core'u free eder.
}
