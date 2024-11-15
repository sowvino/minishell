/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-20 11:54:12 by selango           #+#    #+#             */
/*   Updated: 2024-06-20 11:54:12 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (*str)
	{
		ft_print_char((int)*str);
		count++;
		str++;
	}
	return (count);
}

int	ft_print_digit(long n, int base, int is_upper)
{
	int		count;
	char	*symbols;

	count = 0;
	if (is_upper)
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_digit(-n, base, is_upper) + 1);
	}
	else if (n < base)
		return (ft_print_char(symbols[n]));
	else
	{
		count = ft_print_digit(n / base, base, is_upper);
		return (count + ft_print_digit(n % base, base, is_upper));
	}
}

int	ft_print_hex(unsigned long num, int base);

int	ft_print_pointer(void *ptr)
{
	int		count;
	long	address;

	count = 0;
	address = (unsigned long)ptr;
	if (ptr == 0)
	{
		return (ft_print_str("(nil)"));
	}
	count += ft_print_str("0x");
	count += ft_print_hex(address, 16);
	return (count);
}

int	ft_print_hex(unsigned long num, int base)
{
	char	*symbols;
	char	buffer[20];
	int		i;
	int		count;

	i = 0;
	count = 0;
	symbols = "0123456789abcdef";
	if (num == 0)
		buffer[i++] = '0';
	else
	{
		while (num > 0)
		{
			buffer[i++] = symbols[num % base];
			num /= base;
		}
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
		count++;
	}
	return (count);
}
