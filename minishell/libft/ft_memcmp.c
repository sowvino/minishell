/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:19:58 by selango           #+#    #+#             */
/*   Updated: 2024/06/05 16:07:03 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (i < (n))
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
// int main ()
// {
// 	const char *s1 ="abcdefghij";
// 	const char  *s2 ="abcdefgxyz";
// 	size_t n ;
// 	n = 7;
// 	printf("%d\n", ft_memcmp(s1,s2,n));

// 	printf("%d\n", memcmp(s1,s2,n));
// }
