/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 09:24:47 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 09:24:47 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_totlen(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	totlen;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	totlen = len1 + len2;
	return (totlen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		totlen;
	char	*newstr;
	int		i;
	int		j;

	totlen = ft_totlen((char *)s1, (char *)s2);
	newstr = (char *)malloc((totlen + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

// int main()
// {
// 	const char *s1 = "Hello";
// 	const char *s2 = "worldghh";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }
