/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:35:37 by selango           #+#    #+#             */
/*   Updated: 2025/02/10 17:51:55 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is used to check if the string is empty  
if it empty then it returns the string or
else if it copies the string to the newly allocated result and free the string
This function also clears the unwanted spaces in the quotes and 
gives the result of the string as a proper string*/
static void	process_string(char *str, char *temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i += 2;
		else
			temp[j++] = str[i++];
	}
}

char	*ft_clear_empty_str(char *str)
{
	char	*temp;
	char	*result;
	size_t	line;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	process_string(str, temp);
	free(str);
	line = ft_strlen(temp) + 1;
	result = ft_calloc(line, sizeof(char));
	if (!result)
	{
		free(temp);
		return (NULL);
	}
	ft_strlcpy(result, temp, line);
	free(temp);
	return (result);
}

/*This function expands the given args according the 
signs and return the result*/
static char	*ft_quotes_expander(char *str, t_minishell *minishell_variable)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			result = ft_strjoin_free(result, ft_squotes_handler(str, &i));
		else if (str[i] == '"')
			result = ft_strjoin_free(result,
					ft_dquotes_handler(str, &i, minishell_variable));
		else if (str[i] == '$')
			result = ft_strjoin_free(result,
					ft_dollar_handler(str, &i, minishell_variable));
		else
			result = ft_strjoin_free(result, ft_normal_handler(str, &i));
	}
	return (result);
}

/*This function return the expanded input
// handles the quotes according to the requirements
//clears the unwanted quotes or spaces  given in the input
// it splits the words and returns the words with the quotes.*/
char	**ft_expand(char *str, t_minishell *minishell_variable)
{
	char	**expanded;
	size_t	i;

	i = 0;
	str = ft_quotes_expander(str, minishell_variable);
	if (!str)
		return (NULL);
	str = ft_clear_empty_str(str);
	if (!str)
		return (NULL);
	expanded = ft_expander_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	while (expanded[i])
	{
		expanded[i] = ft_remove_quotes(expanded[i]);
		i++;
	}
	return (expanded);
}
