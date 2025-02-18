/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:31 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:31 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_binary_operation(t_minishell *minishell_variable)
{
	t_token_type	type;

	if (!minishell_variable->current_token)
		return (false);
	type = minishell_variable->current_token->type;
	if (type == TOKEN_PIPE)
		return (1);
	return (0);
}

int	is_redirectory(t_token_type type)
{
	if (type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC
		|| type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		return (1);
	return (0);
}

t_node	*handle_round_paren(t_minishell *minishell_variable)
{
	t_node	*node;

	if (!minishell_variable->current_token ->next)
		return (minishell_variable->pars_error.type = SYNTAX_ERROR, NULL);
	minishell_variable->current_token
		= minishell_variable->current_token->next;
	node = build_ast(0, minishell_variable);
	if (!node)
	{
		minishell_variable->pars_error.type = MEM_ERROR;
		return (NULL);
	}
	if (!minishell_variable->current_token
		|| minishell_variable->current_token->type != TOKEN_RIGHT_PAREN)
	{
		minishell_variable->pars_error.type = SYNTAX_ERROR;
		return (NULL);
	}
	minishell_variable->current_token
		= minishell_variable->current_token->next;
	return (node);
}

int	handle_command_token(t_node *node, t_minishell *minishell_variable)
{
	if (minishell_variable->current_token->type == TOKEN_IDENTIFIER)
	{
		if (!build_identifiers_list(&(node->args), minishell_variable))
		{
			clear_cmd_node(node);
			minishell_variable->pars_error.type = MEM_ERROR;
			return (0);
		}
	}
	else if (is_redirectory(minishell_variable->current_token->type))
	{
		if (!build_io_list(&(node->io_list), minishell_variable))
		{
			free(node->args);
			free(node);
			return (0);
		}
	}
	return (1);
}
