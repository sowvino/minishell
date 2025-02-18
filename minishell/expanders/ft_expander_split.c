/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:18:58 by selango           #+#    #+#             */
/*   Updated: 2025/02/11 18:35:09 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*this function handles memory for storing the words in a array.
it also ensures the quotes are treated as word
// additional plus one for the null terminator operation.*/
static char	**allocators(char *str, char **temp, size_t count)
{
	size_t	begin;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			begin = i;
			skip_words(str, &i);
			temp[j] = ft_calloc((i - begin) + 1, sizeof(char));
			if (!temp[j])
			{
				while (j > 0)
					free(temp[--j]);
				return (free(temp), NULL);
			}
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (temp[count] = NULL, temp);
}

/*This function words_placer */
static void	words_placers(char *str, char **arrs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (str[(*i)] && str[(*i)] != ' ')
	{
		if (str[(*i)] != '\'' && str[(*i)] != '"')
			arrs[j][k++] = str[(*i)++];
		else
		{
			quotes = str[(*i)++];
			arrs[j][k++] = quotes;
			while (str[(*i)] != quotes)
				arrs[j][k++] = str[(*i)++];
			arrs[j][k++] = str[(*i)++];
		}
	}
	arrs[j][k] = '\0';
}

/*This function fills the strings in an array
// fills the words in the place*/
static char	**ft_filler(char *str, char **arrs_to_fill)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && arrs_to_fill[j])
	{
		if (str[i] != ' ')
		{
			words_placers(str, arrs_to_fill, &i, j);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (arrs_to_fill);
}

/* This function handles the string to store in other new 2d array and
 it returns the normal string from another string
  // counts the number of words */

static size_t	count_words(char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			skip_words(str, &i);
			count++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (count);
}

char	**ft_expander_split(char *str)
{
	size_t	count;
	char	**temp;

	if (!str)
		return (NULL);
	count = count_words(str);
	if (!count)
		return (ft_calloc(1, sizeof(char *)));
	temp = ft_calloc(count + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	temp = allocators(str, temp, count);
	if (!temp)
		return (NULL);
	return (ft_filler(str, temp));
}
