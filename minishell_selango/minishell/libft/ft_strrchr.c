/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 13:44:08 by selango           #+#    #+#             */
/*   Updated: 2024-05-22 13:44:08 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	a;
	int		i;

	a = (char)c;
	i = ft_strlen((char *)s);
	if (a == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == a)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = "Hello & world & hello";
// 	int c = '&';
// 	printf("%s\n", ft_strchr(s, c));
// 	printf("%s\n",strrchr(s,c));
// }
