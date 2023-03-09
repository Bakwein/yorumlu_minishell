/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:39:23 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/21 12:03:19 by hsozan           ###   ########.fr       */
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
		g_core.cmd = readline(g_core.title.full_title);
		exit_signal_check(); // ctrl+d sinyali için signalfonksiyonu kullanılır.
		lexer(); // komutu parçalara ayırır.
		expander(); 
		parser(); // komutu parse eder.
		executer(); // komutu çalıştırır.
		update_history(g_core.cmd); // komutu history'e ekler.
		free_for_loop(); // döngüyü freeler
	}
	free_core(); // Core'u free eder.
}
