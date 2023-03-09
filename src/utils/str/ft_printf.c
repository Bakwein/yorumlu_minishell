/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:14:21 by hsozan            #+#    #+#             */
/*   Updated: 2023/03/08 12:14:41 by hsozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdarg.h>
#include <unistd.h>

//ft_printf with s d x X % c p u
int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	if (!s)
		return (ft_putstr("(null)"));
	return (i);
}

int	ft_putnbr_base(unsigned long int n, char *base_c, int base)
{
	int	res;
	int	i;
	int	n_backwards[100];

	res = 0;
	i = 0;
	if (n < 0 && base == 10)
	{
		res += ft_putchar('-');
		n *= -1;
	}
	else if (n == 0)
		return (ft_putchar('0'));
	while (n)
	{
		n_backwards[i] = n % base;
		n /= base;
		i++;
	}
	while (i--)
		res += ft_putchar(base_c[n_backwards[i]]);
	return (res);
}

int	ft_sort(char c, va_list args)
{
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base(va_arg(args, int), "0123456789", 10));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned long int), \
				"0123456789abcdef", 16));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned long int), \
					"0123456789ABCDEF", 16));
	else if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 'p')
		return (ft_putstr("0x") + ft_putnbr_base(va_arg(args, \
					unsigned long int), "0123456789abcdef", 16));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10));
	else
		return (ft_putchar(c));
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			res += ft_sort(s[i], args);
			i++;
		}
		else
		{
			res += ft_putchar(s[i]);
			i++;
		}
	}
	va_end(args);
	return (res);
}
//#include <stdio.h>
//int main()
//{
//   int a = 12;
//
//    ft_printf("%i\n",ft_printf("Hello %s %i %d %x %X %c %p %u %%\n",
//    "World", a, a, a, a, 'A', &a, 42));
//    printf("%i\n",printf("Hello %s %i %d %x %X %c %p %u %%\n",
//    "World", a, a, a, a, 'A', &a, 42));
//
//    return 0;
//}