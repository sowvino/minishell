/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_tokenization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:15 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:15 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creatin a new token and adding it to the token list.
// if
int	add_separator(t_token_type type, char **line, t_token **token_list)
{
	t_token	*token;

	token = new_token(NULL, type);
	if (!token)
		return (0);
	token_list_add_new(token_list, token);
	(*line)++;
	if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_HEREDOC
		|| type == TOKEN_REDIR_APPEND)
		(*line)++;
	return (1);
}

// for >, <, |, && ...
int	separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (add_separator(TOKEN_REDIR_HEREDOC, line, token_list));
	else if (!ft_strncmp(*line, "<", 1))
		return (add_separator(TOKEN_REDIR_IN, line, token_list));
	else if (!ft_strncmp(*line, ">>", 2))
		return (add_separator(TOKEN_REDIR_APPEND, line, token_list));
	else if (!ft_strncmp(*line, ">", 1))
		return (add_separator(TOKEN_REDIR_OUT, line, token_list));
	else if (!ft_strncmp(*line, "(", 1))
		return (add_separator(TOKEN_LEFT_PAREN, line, token_list));
	else if (!ft_strncmp(*line, ")", 1))
		return (add_separator(TOKEN_RIGHT_PAREN, line, token_list));
	else
		return (add_separator(TOKEN_PIPE, line, token_list));
}
