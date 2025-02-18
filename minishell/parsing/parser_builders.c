/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:04 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:04 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a string from identifiers,
// separates them with ' ' and give
// the result to the variable *args
int	build_identifiers_list(char **args, t_minishell *minishell_variable)
{
	char	*temp;

	if (minishell_variable->pars_error.type)
		return (0);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (0);
	while (minishell_variable->current_token
		&& minishell_variable->current_token->type
		== TOKEN_IDENTIFIER)
	{
		temp = *args;
		*args = ft_strjoin_with(*args,
				minishell_variable->current_token->value, ' ');
		if (!*args)
		{
			free(temp);
			return (0);
		}
		free(temp);
		minishell_variable->current_token
			= minishell_variable->current_token->next;
	}
	return (1);
}

static int	build_io_list2(t_io_node	**temp_io_node,
	t_minishell *minishell_variable, t_token_type redirection_type)
{
	if (!minishell_variable->current_token
		||minishell_variable->current_token->type != TOKEN_IDENTIFIER)
	{
		minishell_variable->pars_error.type = SYNTAX_ERROR;
		return (0);
	}
	*temp_io_node = new_io_node(redirection_type,
			minishell_variable->current_token->value);
	if (!*temp_io_node)
	{
		minishell_variable->pars_error.type = MEM_ERROR;
		return (0);
	}
	return (1);
}

// funcrion for creating separators list
int	build_io_list(t_io_node **io_list, t_minishell *minishell_variable)
{
	t_token_type	redirection_type;
	t_io_node		*temp_io_node;

	if (minishell_variable->pars_error.type)
		return (0);
	while (minishell_variable->current_token
		&& is_redirectory(minishell_variable->current_token->type))
	{
		redirection_type = minishell_variable->current_token->type;
		minishell_variable->current_token
			= minishell_variable->current_token->next;
		if (!build_io_list2(&temp_io_node,
				minishell_variable, redirection_type))
			return (0);
		append_io_node(io_list, temp_io_node);
		minishell_variable->current_token
			= minishell_variable->current_token->next;
	}
	return (1);
}

// the function builds a command
// the while loop works while there are
// tokens and those tokens are identifiers or specifiers
t_node	*build_command(t_minishell *minishell_variable)
{
	t_node	*node;

	if (minishell_variable->pars_error.type)
		return (NULL);
	node = new_node(CMD_NODE);
	if (!node)
	{
		minishell_variable->pars_error.type = MEM_ERROR;
		return (NULL);
	}
	while (minishell_variable->current_token
		&& (minishell_variable->current_token->type
			== TOKEN_IDENTIFIER
			|| is_redirectory(minishell_variable->current_token->type)))
	{
		if (!handle_command_token(node, minishell_variable))
			return (NULL);
	}
	return (node);
}
