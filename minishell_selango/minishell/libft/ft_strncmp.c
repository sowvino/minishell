/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:36 by selango           #+#    #+#             */
/*   Updated: 2024/06/05 16:19:03 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		if (s1[i] == '\0' && s2[i] != '\0')
			return (-1);
		if (s1[i] != '\0' && s2[i] == '\0')
			return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	char			*a;
// 	char			*b;
// 	unsigned int	c;

// 	a = "helloa";
// 	b = "helloiom";
// 	c = 6;

// 	printf("%d\n", ft_strncmp(a, b, c));
// 	printf("%d\n",strncmp(a,b,c));
// }
