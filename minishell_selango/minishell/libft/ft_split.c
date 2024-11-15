/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-29 08:32:24 by selango           #+#    #+#             */
/*   Updated: 2024-05-29 08:32:24 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	f;
	int	count;

	i = 0;
	count = 0;
	f = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			f = 0;
		else if (f == 0)
		{
			f = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_createwords(const char *s, char c)
{
	char	*des;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	des = (char *)malloc(sizeof(char) * (i + 1));
	if (des == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		des[i] = s[i];
		i++;
	}
	des[i] = '\0';
	return (des);
}

static char	**ft_free(char **split, int i)
{
	while (i > 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			arr[j] = ft_createwords(&s[i], c);
			j++;
			if (arr[j - 1] == NULL)
				return (ft_free(arr, j));
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	arr[j] = NULL;
	return (arr);
}

// int main()
// {
// 	const char *s ="Hello,world,hi\\there,prague,42";
// 	char c = '\\';
// 	char **split ;
// 	int  i;
// 	split = ft_split(s,c);
// 	  for (i = 0; split[i] != NULL; i++)
//     {
//         printf("Word %d: %s\n", i + 1, split[i]);

//     }

// }
