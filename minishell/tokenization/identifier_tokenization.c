/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_tokenization.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:09 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:09 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char *s)
{
	if (*s == '<' || *s == '>' || *s == '|' || *s == '('
		|| *s == ')' || !ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t')
		return (1);
	else
		return (0);
}

//it checks if quote has a pair. It also 
// skips everything which is inside the string
bool	skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

// the function checks if quotes closed correctly, 
// handles with spaces like in "hello world" or supress 
// metacharacters like in the example "echo '$HOME'"
int	quotes_handler(char *tmp_line, size_t *i, t_minishell *minishell_variable)
{
	while (tmp_line[*i]
		&& !is_separator(tmp_line + *i))
	{
		if (tmp_line[*i] == '\'' || tmp_line[*i] == '"')
		{
			if (!skip_quotes(tmp_line, i))
			{
				ft_putstr_fd("Error with ", 2);
				ft_putchar_fd(tmp_line[*i], 2);
				ft_putchar_fd('\n', 2);
				minishell_variable->exit_s = 258;
				return (0);
			}
		}
		else
			(*i)++;
	}
	return (1);
}

// for commands echo, cd, pwd ...
// we use tmp_line to not to change the original line, 
// because changing may cause problems
// we adding quote handlers into a condition, 
// because there might be unclosed quotation marks which can casue a problem.
int	identifier(char **line, t_token **token_list,
				t_minishell *minishell_variable)
{
	char	*tmp_line;
	size_t	i;
	char	*value;
	t_token	*token;

	tmp_line = *line;
	i = 0;
	if (!quotes_handler(tmp_line, &i, minishell_variable))
		return (0);
	while (tmp_line[i] == ' ' || tmp_line[i] == '\t')
		i++;
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = new_token(value, TOKEN_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line += i;
	return (token_list_add_new(token_list, token), 1);
}
