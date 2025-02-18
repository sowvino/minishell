/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:58 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:58 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the function for terminal elements
// first cheking for existence of tocken, 
// that it is not a binary operation and that it is not a right parenth
// when checking if currnt token 
// is a left parenth. here we are moving to the next token 
// and build_ast again for processing the expression in parentheses
// if expression is fine and it doesn't start from (, then we build a command
t_node	*term(t_minishell *minishell_variable)
{
	if (minishell_variable->pars_error.type)
		return (NULL);
	if (!minishell_variable->current_token
		|| is_binary_operation(minishell_variable)
		|| minishell_variable->current_token->type == TOKEN_RIGHT_PAREN)
	{
		minishell_variable->pars_error.type = SYNTAX_ERROR;
		return (NULL);
	}
	if (minishell_variable->current_token->type == TOKEN_LEFT_PAREN)
		return (handle_round_paren(minishell_variable));
	else
		return (build_command(minishell_variable));
}

// creates a new ast node
// for example: a|b : initial_symbol = a, rest = b, operator = |
t_node	*build_ast_node( t_node *initial_symbol,
			t_node *rest, t_minishell *minishell_variable)
{
	t_node	*node;

	if (minishell_variable->pars_error.type)
		return (NULL);
	node = new_node(node_type());
	if (!node)
	{
		minishell_variable->pars_error.type = MEM_ERROR;
		return (NULL);
	}
	node ->left = initial_symbol;
	node -> right = rest;
	return (node);
}

t_node	*proces_binop(t_node *initial_symbol,
	int min_priority, t_minishell *minishell_variable)
{
	int				new_priority;
	t_node			*rest;

	while (is_binary_operation(minishell_variable)
		&& priority() >= min_priority)
	{
		minishell_variable->current_token
			= minishell_variable->current_token->next;
		if (!minishell_variable->current_token)
		{
			minishell_variable->pars_error.type = SYNTAX_ERROR;
			return (initial_symbol);
		}
		new_priority = priority() + 1;
		rest = build_ast(new_priority, minishell_variable);
		if (!rest)
			return (initial_symbol);
		initial_symbol = build_ast_node(initial_symbol,
				rest, minishell_variable);
		if (!initial_symbol)
			clear_i_s(&initial_symbol, &rest, minishell_variable);
	}
	return (initial_symbol);
}

// this is a function for binary operations such as > < >> << | && ||
// it cteates ast
// if parsing error != 0 or there are no tokens, 
// the function returns 0 which means that we have an error
// term function helps to get the first symbol of the string
// when there is a while loop. It checks if the next 
// token after the first one is an operator. we save that 
// token-operator in the variable "operator". 
// and then we are checkin the next token. 
// if it doesn't exist, function stops.
// The higher the priority, the lower the value of new_priority
t_node	*build_ast(int min_priority, t_minishell *minishell_variable)
{
	t_node			*initial_symbol;

	if (minishell_variable->pars_error.type
		|| !minishell_variable->current_token)
		return (NULL);
	initial_symbol = term(minishell_variable);
	if (!initial_symbol)
		return (NULL);
	return (proces_binop(initial_symbol, min_priority, minishell_variable));
}

// *ast is an abstract syntax tree. so the variable contains the tree.
// we are setting current token to the first token in the token's list.
// if there are more tokens after build_ast it means that we have 
// an error, because there suposse to be no tokens after building ast
// if building is correct we reterns ast
// we give to build ast priority 0 because it is initial symbol
t_node	*parsing(t_minishell *minishell_variable)
{
	t_node	*ast;

	minishell_variable->current_token = minishell_variable->tokens;
	ast = build_ast(0, minishell_variable);
	if (minishell_variable->current_token)
	{
		minishell_variable->pars_error.type = SYNTAX_ERROR;
		return (ast);
	}
	return (ast);
}
