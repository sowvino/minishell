/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 08:42:27 by selango           #+#    #+#             */
/*   Updated: 2024-05-22 08:42:27 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	char dest[] = "hello";
// 	const char src[] = "world";
// 	size_t n = 5;
// 	ft_memcpy(dest, src, n);
// 	printf("%s\n", dest);
// 	return (0);
// }
