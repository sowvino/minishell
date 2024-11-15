/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:57:45 by selango           #+#    #+#             */
/*   Updated: 2024/06/05 13:27:25 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		len;

	len = 0;
	while (src[len] != '\0')
		len++;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (len >= 0)
	{
		new[len] = src[len];
		len--;
	}
	return (new);
}

// int	main(void)
// {
// 	char	*a;

// 	a = "Hello";
// 	printf("%s\n", ft_strdup(a));
// }
