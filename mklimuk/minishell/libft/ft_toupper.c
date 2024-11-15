/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 09:05:20 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 09:05:20 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int ch)
{
	if (ch >= 97 && ch <= 122)
	{
		return (ch - 32);
	}
	return (ch);
}

// int main()
// {
// 	int ch = 98;
// 	printf("%d", toupper(ch));
// }