/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 10:56:57 by selango           #+#    #+#             */
/*   Updated: 2024-05-22 10:56:57 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dest_len = (size_t)ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (size <= dest_len)
		return (size + src_len);
	i = dest_len;
	j = 0;
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

// int	main(void)
// {
// 	char src[] = "World!";
// 	char dest[] = "Hello ";
// 	printf("%zu | %s\n", ft_strlcat(dest, src, 12), dest);
// }
