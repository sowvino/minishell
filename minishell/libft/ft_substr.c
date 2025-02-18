/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 09:07:06 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 09:07:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	strlength;

	i = 0;
	if (s == NULL)
		return (NULL);
	strlength = ft_strlen((char *)s);
	if (start >= strlength)
		return (ft_strdup(""));
	if (start + len > strlength)
		len = strlength - start;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// int main()
// {
// 	const char *s = "hello world";
// 	unsigned int start = 7;
// 	size_t len = 6;
// 	printf("%s\n", ft_substr(s, start, len));
// }
