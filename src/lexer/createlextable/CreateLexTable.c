/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateLexTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:37:20 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:37:20 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	Count degiskenine komutun ne kadar genislikte olmasi gerektigi get_cmdlen 
	fonksiyonu ile atanir.
	count buyuklugu kadar bellekte alan acilir ve bu alana count
	degiskeninde ki miktar kadar atanir.
	komutun adresi cmd_line degiskeninde tutuldugundan dolayi adres 
	uzerinden arttirilma islemleri yapilir.
	Boylece fonksiyonun cagirildigi yerde de adres arttirilmis olur.
*/
void	parse_cmd(char **cmd_line, t_lexlist *last_node)
{
	size_t	count;
	char	*holder_content;

	count = get_cmdlen(*cmd_line); // ayıracağı yere kadar olan uzunluğu alır(ALACAĞI PARÇA UZUNLUĞU)
	holder_content = (char *)malloc(sizeof(char) * (count) + 1); // +1 null
	last_node->content = holder_content; // node'un içine atar
	holder_content[count] = 0; // count. indise yani sonuna null atar
	while (count--) // count 0 olana kadar cmd_line'daki komutu holder_content'e atar
		*(holder_content++) = *((*cmd_line)++);
}

/*
	Gelen komutta oncelikle bosluklar gecilir ardindan komutta sona gelinip
 	gelinmedigi kontrol edilir, gelde ise fonksiyon sonlandirilir.
	Eger sona gelinmedi ise yeni lexer listesinde yeni bir node olusturulur
	 ve olusturulan yeni node komut ayiriciya gonderilir.
	Ardindan recurisive ile komut sona gelene kadar fonksiyon tekrardan cagirilir.
*/
void	create_lexlist(char *cmdline, t_lexlist **lex_table)
{
	t_lexlist	*last_node;

	trim_spaces(&cmdline); // baştaki boşlukları atlar adresi space kadar ilerletilir.
	if (!cmdline || !*cmdline) // varsa boşlukları geçtikten sonra komut boşsa(RECURSIVE BURADA SONA ERER)
		return ;
	last_node = add_new_lex_node(lex_table); // yeni bir node oluşturur.default atamaları yapar
	parse_cmd(&cmdline, last_node); // node'u parse eder
	create_lexlist(cmdline, lex_table); // parse'de son işlemde önceki node'un contentinden sonra değer adres(CMDLINE ADRESİ) olarak kaldı her seferinde o adres güncellene güncellene recursive gibi devam eder
	//recursive gibi sona geldiğinde üstteki if'e gireceğinden fonksiyon sonlanır
}
