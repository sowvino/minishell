/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:31 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:31 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

// the function takes user's line and cuts it into list of tokens
// it separates diffenet elements of 
// line such as >, <, |, &&, (, ) and identifiens
t_token	*tokenization_handler(char *line, t_minishell *minishell_variable)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (clean_token_list(&token_list), NULL);
		if (is_space(*line))
			line++;
		if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
		{
			if (!separator(&line, &token_list))
				error = 1;
		}
		else
		{
			if (!identifier(&line, &token_list, minishell_variable))
				error = 1;
		}
	}
	return (token_list);
}

// it takes user's input and processes it char by char into tokens
// most important thing is type of tokens and their order - not values
t_token	*tokenization(t_minishell *minishell_variable)
{
	char	*line;
	t_token	*tokens;

	line = minishell_variable->line;
	tokens = tokenization_handler(line, minishell_variable);
	free (line);
	minishell_variable->line = NULL;
	return (tokens);
}
