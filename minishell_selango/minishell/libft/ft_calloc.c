/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 11:08:53 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 11:08:53 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*array;

	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	if (nelem != 0 && elsize != 0 && (nelem * elsize) / elsize != nelem)
		return (NULL);
	array = malloc(nelem * elsize);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (nelem * elsize));
	return (array);
}

// int main()
// {
// 	size_t nelem = 2;
// 	size_t elsize = 4;
// 	char *ret = ft_calloc(nelem, elsize);
// 	printf("%s\n", ret);
// }
