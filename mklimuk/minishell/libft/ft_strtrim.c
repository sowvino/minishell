/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-28 11:23:26 by selango           #+#    #+#             */
/*   Updated: 2024-05-28 11:23:26 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
/* find the first_pos of original string and check if it contains set in it */

int	first_pos(const char *s, const char *set)
{
	int	i;

	i = 0;
	while (s[i] && is_set(s[i], (char *)set))
	{
		i++;
	}
	return (i);
}
/* find the last_pos of original string and check if it contains set in it */

int	last_pos(const char *s, const char *set)
{
	int	i;

	i = ft_strlen((char *)s) - 1;
	while (i >= 0 && is_set(s[i], (char *)set))
	{
		i--;
	}
	return (i);
}
/*finding the correct length of the new_string*/

int	trim_len(const char *s, const char *set)
{
	int	last;
	int	first;

	last = last_pos(s, set);
	first = first_pos(s, set);
	if (last < first)
		return (0);
	return (last - first + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		newstr_len;
	int		i;
	char	*str;
	int		start;

	str = (char *)s1;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	newstr_len = trim_len(str, (char *)set);
	new_str = (char *)malloc((newstr_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	start = first_pos(str, (char *)set);
	while (i < newstr_len)
	{
		new_str[i] = str[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}
// int main()
// {
// 	const char *s = "1234helloworld4";
// 	const char *set = "123";
// 	printf("%s\n",ft_strtrim(s,set));
// }
