/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetLen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:37:30 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:37:30 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
	c karakterine komutun ilk indisi atanir ve hangi tirnak
	tipi oldugu anlasilir(" ya da ').
	komut nulla gelene kadar(pdf tirnagin kapatilmis olup olmadıgini
	 kontrol etmemizi istemiyor)
	ya da baslangic karakterine gorene kadar count degiskeni arttilir.
	ve bu degisken return edilir.
*/
size_t	get_quotelen(char *cmd_line)
{
	char	c;
	size_t	count;

	c = *cmd_line;
	count = 1;
	while (*(++cmd_line)) // baştan arttırarak ilk karakteri atlar diğerini bulmak için ilerler
	{
		count++;
		if (*cmd_line == c) // diğerinin bulduğunda girer
			break ;
	}
	return (count); // uzunluğunu döndürür
}

/*
	Bu fonksiyon her cagirildiginda kelime uzunlugunu alir.
	Ve uzunlugu donderir.
	Eger komutun indisi metakarakter ise metakarakterin
	genisligi count'a eklenir ve dongu sonlandirilir.
	Eger komutun indisinde tirnak isareti var ise get_quotelen
	fonksiyonundan tirnagin ve icinin ne kadar uzunkukta oldugu alinir
	ve ardindan counta eklenir.
	Eger komutun indisi metakarakter ya da tirnak degilse count arttirlir.
	orn:
	cat a.txt -> cat'in uzunlugu olan 3'u donderir
	<< "eof" cat -> <<'un uzunlugu olan 2'yi donderir
	"Ahmet$HOME"ls echo -> "Ahmet$HOME"ls'in uzunlugu olan 14'u gonderir
	gelen komut null'a gelene ya da bosluga gelene kadr donderilir.
*/
size_t	get_cmdlen(char *cmd_line)
{
	size_t	count;
	size_t	quotelen;
	char	*is_meta;

	count = 0;
	while (cmd_line && *cmd_line && *cmd_line != ' ') // komut null'a gelene kadar veya bosluga gelene kadar devam eder
	{
		is_meta = compare_metachars(cmd_line); // komutun indisi metakarakter mi diye kontrol edilir
		if (is_meta) // eger metakarakter ise
		{
			if (!count) // eger count 0 ise (başlangıçta mı)
				count += ft_strlen(is_meta); // alınan metakarakterin uzunluğunu count'a ekler
			break ; 
		}
		if ((*cmd_line == *SINGLE_QUOTE || *cmd_line == *DOUBLE_QUOTE)) // eger komutun indisi ' ve " ise
		{
			quotelen = get_quotelen(cmd_line); // komutun indisi tirnagin uzunlugunu alir
			count += quotelen; // count'a ekler
			cmd_line += quotelen; // cmd_line adres olarak tirnagin uzunluguna kadar ilerler
			// bunun nedeni tırnaktan sonra ayrı olmayan karakterleri de almak istemesi echo "asdhas"bs -> asdhasbs
			continue ; // altta da arttırmasın diye continue
		}
		count++; // eger komutun indisi metakarakter ya da tirnak degilse ve space ne NULL ile karşılaşmadığı sürece count arttırılır ve cmd line adresi ilerletilir.
		cmd_line++;
	}
	return (count); // sonda çıkan count'u dondurur
}
