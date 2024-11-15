/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-30 10:57:30 by selango           #+#    #+#             */
/*   Updated: 2024-05-30 10:57:30 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)( unsigned int, char*))
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
// void my_function(unsigned int i, char *s)
// {
// 	i = 0;
// 	while(s[i] >= 'a' && s[i] <= 'z')
//     {
//         s[i] = s[i] -32;
// 		i++;
//     }
// }

// int main()
// {
// 	char s[]= "aBc";
// 	ft_striteri(s, my_function);
// 	printf("%s\n" , s);
// }
