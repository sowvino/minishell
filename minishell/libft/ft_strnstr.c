/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 08:46:06 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 08:46:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[i] == '\0')
		return ((char *)&str1[i]);
	while (str1[i] != '\0' && i < len)
	{
		j = 0;
		while (i + j < len && str2[j] != '\0' && str1[i + j] == str2[j])
			j++;
		if (str2[j] == '\0')
			return ((char *)&str1[i]);
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	char *str1 = "aaabcabcd";
// 	char *str2 = "aaabc";
// 	size_t n = 5;
// 	printf("%s\n", ft_strnstr(str1, str2, n));
// }
