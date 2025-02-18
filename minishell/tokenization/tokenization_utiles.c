/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utiles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:24 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:24 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// it's a function which creates a new token
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	return (new_token);
}

// adding a new token to the end of the token list
void	token_list_add_new(t_token **token_list, t_token *new_token)
{
	t_token	*current;

	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	current = *token_list;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	clean_token_list(t_token **token_list)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *token_list;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		if (curr_node != NULL)
		{
			free(curr_node->value);
			next = curr_node->next;
			free(curr_node);
			curr_node = next;
		}
	}
	*token_list = NULL;
}
