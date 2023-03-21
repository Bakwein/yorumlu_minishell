/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetMissingArg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:38:29 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:38:29 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_missing_arg(void)
{
	char	*ptr;
	int		fd[2];
	char	c[1];

	pipe(fd);
	if (!read_missing_arg(fd)) 
		return (NULL);
	ptr = NULL;
	while (read(fd[0], c, 1)) // fd[0]'daki değeri 1 byte okur c'ye yazar
		str_addchar(&ptr, *c); //c'yi ptr'ye baştan sonra teker teker yazar.
	close(fd[0]);  // read için kullanılan fd[0] kapatılır.
	return (ptr);
}
/*
pipe(fd) işlevi, UNIX sistemlerinde iki dosya tanımlayıcısı arasında bir boru hattı (pipe) oluşturur. Bu işlev, bir dizi işlem tarafından paylaşılan bir iletişim kanalı sağlar.
pipe(fd) işlevi, bir dizi dosya tanımlayıcısı verir. fd[0] okuma için kullanılırken, fd[1] yazma için kullanılır. pipe işlevi, bu iki dosya tanımlayıcısını içeren bir dizi oluşturur. Bu dizi, okuma ve yazma işlemlerinde kullanılabilir.
Bir örnek olarak, bir işlem veri üretirken, diğer bir işlem bu verileri alabilir ve işleyebilir. pipe işlevi, iki işlem arasında veri iletişimi sağlar.
*/

int	read_missing_arg(int *fd)
{
	int		pid;
	int		return_value;

	pid = -1;
	pid = fork(); // pid -> 0
	g_core.pid = pid;
	g_core.is_read_arg = 1; // ctrl + c için kontrol başlangıcı
	if (!pid) // pid -> 0
		read_missing_arg_value(fd);
	close(fd[1]); // write için kullanılan fd[1] kapatılır.
	waitpid(pid, &return_value, 0); //waitpid() işlevi, belirli bir çocuk sürecin sonlanmasını bekleyen bir ebeveyn süreç tarafından kullanılır. pid parametresi ile beklenen çocuk sürecin kimliği (PID) belirtilir. return_value ise, çocuk sürecin sonlanma durumunu tutan bir değişkenin adresidir. 0 seçeneği ise, waitpid() işleminin engellenmeden devam etmesini ve beklenen çocuk sürecin sonlanmasını beklemesini belirtir.
	g_core.is_read_arg = 0; // ctrl + c için kontrol sonu
	return_value = WEXITSTATUS(return_value); // WEXITSTATUS() işlevi, çocuk sürecin sonlanma durumunu döndürür. Çocuk sürecin sonlanma durumu, çocuk sürecin exit() işleviyle döndürdüğü değerdir.
	if (return_value == SIGNAL_C) // eğer 32 döndüyse ctrl + c basılmış demektir.
	{
		close(fd[0]); // read için kullanılan fd[0] kapatılır.
		update_history(g_core.cmd); //history'i günceller. üst yön tuşuna basıldığında sanki yan yana yazılmış gibi gözükür
		free_for_loop(); // for döngüsü için kullanılan değerlerin hepsi free edilir.
		return (0);
	}
	return (1);
}

void	read_missing_arg_value(int *fd)
{
	char	*ptr;

	close(fd[0]);
	while (1)
	{
		ptr = readline("> ");
		if (!control_valid_arg(ptr)) //trim_space vs yapıldığında ptr hala boş olup olmadığı kontrol edilir. öyleyse girer.
			continue ;
		write(fd[1], ptr, ft_strlen(ptr)); // fd[1] -> write için kullanılır. fd[0] -> read için kullanılır.
		close(fd[1]); // write için kullanılan fd[1] kapatılır.
		free(ptr); // ptr -> readline fonksiyonu ile alınan değerdir.
		free_for_loop(); // for döngüsü için kullanılan değerlerin hepsi free edilir.
		free_core(); // core için kullanılan değerlerin hepsi free edilir.
		exit(EXIT_SUCCESS); // exit(0)
	}
}
/*
close(fd[0]) işlevi, bir dosya tanımlayıcısının (file descriptor) kullanımını sonlandırır. Bu işlev, pipe işleviyle oluşturulan boru hattında okuma işlemi için kullanılan dosya tanımlayıcısını (fd[0]) kapatır.
Bu işlev, özellikle bir işlem bir veri akışı oluştururken, diğer işlem bu verileri okuyacak şekilde tasarlanmış programlarda kullanılır. Bir işlem, okuma işlemi tamamlandıktan sonra, okuma için kullanılan dosya tanımlayıcısını kapatır (close(fd[0])). Bu, diğer işlemin dosyaya erişimini engeller ve böylece veri bütünlüğünü korur.
Özetle, close(fd[0]) işlevi, pipe işleviyle oluşturulan boru hattında okuma işlemi için kullanılan dosya tanımlayıcısını kapatır ve veri bütünlüğünü korur.
*/

int	control_valid_arg(char *ptr)
{
	char	*str;

	if (!ptr)
		return (0);
	str = ptr;
	trim_spaces(&str);
	if (!*str)
	{
		free(ptr);
		return (0);
	}
	return (1);
}
