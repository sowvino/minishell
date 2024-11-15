/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 08:32:40 by selango           #+#    #+#             */
/*   Updated: 2024-05-22 08:32:40 by selango          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char s[30] = "hello";
// 	size_t n = 1;
// 	ft_bzero(s,n);
// 	printf("%s\n",s);
// }
