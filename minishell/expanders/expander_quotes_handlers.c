/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes_handlers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:29 by selango           #+#    #+#             */
/*   Updated: 2025/02/10 17:36:04 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function handles the $ sign and $? from  the env_variable */
char	*ft_dollar_handler(char *str, size_t *i,
			t_minishell *minishell_variable)
{
	size_t	begin;
	char	*var;
	char	*environ_val;

	begin = *i;
	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(minishell_variable->exit_s));
	}
	else if (!ft_char_checker(str[*i]))
		return (ft_strdup("$"));
	begin = *i;
	while (ft_char_checker(str[*i]))
		(*i)++;
	var = ft_substr(str, begin, *i - begin);
	environ_val = ft_search_envlist(var, minishell_variable);
	if (!environ_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(environ_val));
}

/*This function handles the normal string retuning the orginal string
		// checks if it contains special characters*/
char	*ft_normal_handler(char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '$' && str[*i] != '"')
		(*i)++;
	return (ft_substr(str, begin, *i - begin));
}

/*This function handles the single quotation of the string and
returns the string with the single quotes
// increments until it finds the single quotation
// increments to close the single quotes or just increments*/
char	*ft_squotes_handler(char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, begin, *i - begin));
}

static char	*ft_handle_dquotes_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/*This function handles the double quotation input and
returns the string with double quotation
// checks if the dollar handler is present
// closes the double quotation with the double quotation*/
char	*ft_dquotes_handler(char *str, size_t *i,
		t_minishell *minishell_variable)
{
	char	*res;

	res = ft_strdup("\"");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			res = ft_strjoin_free
				(res, ft_dollar_handler(str, i, minishell_variable));
		else
			res = ft_strjoin_free(res, ft_handle_dquotes_str(str, i));
	}
	if (str[*i] == '"')
		(*i)++;
	return (ft_strjoin_free(res, ft_strdup("\"")));
}
