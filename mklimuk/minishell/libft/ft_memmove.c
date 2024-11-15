/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 09:21:10 by selango           #+#    #+#             */
/*   Updated: 2024-05-22 09:21:10 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src)
	{
		return (dest);
	}
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}
// int main()
// {
// 	char dest[] = "hello";
// 	const char src[] = "wor";
// 	size_t n = 0;
// 	ft_mem_move(dest, src, n);
// 	printf("%s\n", dest);
// 	memmove(dest,src,n);
// 	printf("%s\n",dest);
// 	return 0;
// }
