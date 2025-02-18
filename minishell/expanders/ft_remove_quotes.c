/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:12:00 by selango           #+#    #+#             */
/*   Updated: 2025/02/10 17:23:30 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	handle_quotes(char *str, size_t *i, char *quotes, size_t len)
{
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (!*quotes)
			*quotes = str[*i];
		else if (str[*i] == *quotes)
		{
			(*i)++;
			*quotes = 0;
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	return (len);
}

static size_t	ft_strlen_quotes(char *str)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		len = handle_quotes(str, &i, &quotes, len);
		if (!quotes)
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	ft_quotes_filler(char *str, size_t *i, char *ret, size_t *j)
{
	char	quotes;

	quotes = str[(*i)++];
	while (str[*i] != quotes)
		ret[(*j)++] = str[(*i)++];
	if (str[*i] == quotes)
		(*i)++;
}

char	*ft_remove_quotes(char *str)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0 ;
	j = 0;
	result = ft_calloc(ft_strlen_quotes(str) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_quotes_filler(str, &i, result, &j);
		else
			result[j++] = str[i++];
	}
	free(str);
	return (result);
}
