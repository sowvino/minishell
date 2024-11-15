/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-03-05 16:32:53 by selango           #+#    #+#             */
/*   Updated: 2024-03-05 16:32:53 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// int	main(void)
// {
// 	char	*k;

// 	k = "apnfjnffkdk";
// 	ft_isalpha(k);
// 	printf("%d\n", ft_isalpha(k));
// }
