/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-23 09:25:38 by selango           #+#    #+#             */
/*   Updated: 2024-05-23 09:25:38 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		a;
	size_t				i;
	const unsigned char	*s;

	a = (unsigned char)c;
	s = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == a)
		{
			return ((unsigned char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	const char s[] = "Hello & world &";
// 	int c = '&';
// 	size_t n = 7;
// 	char *res = ft_memchr(s,c , n);
// 	printf("%s\n", res);
// 	char *rest = memchr(s,c,n);
// 	printf("%s\n", rest);
// }
