/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunExit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:31:43 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:31:43 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_all_numeric(char *text)  // hepsi 0 mı kontrolü
{
	while (text && *text)
	{
		if (!(*text >= '0' && *text <= '9'))
			return (0);
		text++;
	}
	return (1);
}

void	run_exit(t_cmdlist *cmd_node)
{
	int	array_len;

	array_len = get_array_len(&cmd_node->path[1]);
	if (array_len > 1)
	{
		print_error("bash: exit: too many arguments\n", NULL, NULL); // exit ab c veya exit(ab c) gibi
		g_core.exec_output = 1;
		return ;
	}
	else if (array_len == 1)
	{
		if (is_all_numeric(cmd_node->path[1])) // exitden sonra sayı var mı kontrolü 0 hata 1 doğru
			g_core.exec_output = ft_atoi(cmd_node->path[1]); // sayı ile exit kullandığımızda echo $? yaptığımızdaki sonuç için g_core.exec_output değişkenine atıyoruz
		else // exit 1.2   veya   exit abc  gibi bir şey yazdığımızda
		{
			print_error("bash: exit: ",
				cmd_node->path[1], ": numeric argument required\n");
			g_core.exec_output = 255;
		}
	}
	else // array_len == 0 ise
		g_core.exec_output = 0;
	free_for_loop(); // klasik freelemek için
	free_core();
	exit(g_core.exec_output % 256); //BUNA BAK!!!!amaçlanan, çıktının yalnızca en alt 8 bitini alarak bir çıkış durum kodu olarak kullanmaktır.
}
