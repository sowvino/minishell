/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:43:25 by selango           #+#    #+#             */
/*   Updated: 2025/02/11 18:35:07 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function returns the joined string and then free the mem of the str
// uses calloc for dynamic alloction of mem*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t		totlen;
	char		*new_str;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	totlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = ft_calloc(totlen, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = 0;
	return (free (s1), free (s2), new_str);
}

/*This function checks if the char is valid are not */
bool	ft_char_checker(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/*This function skips the words in the input 
it stores the quotation in the quotes*/
void	skip_words(char *str, size_t *i)
{
	char	quotes;

	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			(*i)++;
		else
		{
			quotes = str[(*i)++];
			while (str[*i] && str[*i] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}
