/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-18 14:56:36 by selango           #+#    #+#             */
/*   Updated: 2024-06-18 14:56:36 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += ft_print_pointer(va_arg(ap, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_digit((long)va_arg(ap, int), 10, 0);
	else if (specifier == 'u')
		count += ft_print_digit((unsigned long)va_arg(ap, unsigned int), 10, 0);
	else if (specifier == 'x')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 16, 0);
	else if (specifier == 'X')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 16, 1);
	else if (specifier == '%')
		count += ft_print_char('%');
	else
		return (0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count += print_format(*format, ap);
		}
		else
			count += ft_print_char(*format);
		format++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	int	a;
// 	int	*c;

// 	a = -7;
// 	c = &a;
// 	printf("Hello %s,today is %p,in hex %X,char in %c\n", "sowmi", c, 42, 'c');
// 	ft_printf("Hello %s,today is %p,in hex %X,char in %c\n", "sowmi", c, 42,
// 		'c');
// 	return (0);
// }
