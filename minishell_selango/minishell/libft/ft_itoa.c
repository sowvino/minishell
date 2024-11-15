/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-29 10:42:31 by selango           #+#    #+#             */
/*   Updated: 2024-05-29 10:42:31 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long int	abs_value(long int nbr)
{
	int	n;

	n = 1;
	if (nbr < 0)
	{
		n *= -nbr;
	}
	else
		n *= nbr;
	return (n);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*str;
	int				numlen;
	int				sign;
	
	sign = 0;
	if (n < 0)
		sign = 1;
	numlen = get_len(n);
	str = (char *)malloc(sizeof(char) * (numlen + 1));
	if (str == NULL)
		return (NULL);
	str[numlen] = '\0';
	nbr = abs_value(n);
	while (numlen--)
	{
		str[numlen] = 48 + nbr % 10;
		nbr = nbr / 10;
	}
	if (sign)
		*str = 45;
	return (str);
}
// int main()
// {
// 	int n = -2147483648;
// 	printf("%s\n", ft_itoa(n));
// }
