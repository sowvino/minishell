/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-21 10:49:02 by selango           #+#    #+#             */
/*   Updated: 2024-05-21 10:49:02 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int a, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = a;
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char str[30] = "hello";
// 	int a = '$';
// 	size_t n = 2;
// 	ft_memset(str + 2,a,n);
// 	printf("%s\n",str );
// }
