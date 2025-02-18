/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaners.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:36 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:36 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_io_list(t_io_node **lst)
{
	t_io_node	*current_node;
	t_io_node	*next_node;

	current_node = *lst;
	if (!current_node)
		return ;
	while (current_node)
	{
		free(current_node->value);
		free_2d_array(current_node->expanded_value);
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node -> args);
	free_2d_array(node -> expanded_args);
}

void	recursive_clear_cmd(t_node *node)
{
	if (!node)
		return ;
	if (node->type == CMD_NODE)
		clear_cmd_node(node);
	else
	{
		if (node->left)
			recursive_clear_cmd(node->left);
		if (node->right)
			recursive_clear_cmd(node->right);
	}
	free (node);
}

void	clear_ast(t_node **ast, t_minishell *minishell_variable)
{
	recursive_clear_cmd(*ast);
	*ast = NULL;
	clean_token_list(&minishell_variable->tokens);
}

t_node	*clear_i_s(t_node **initial_symbol,
	t_node **rest, t_minishell *minishell_variable)
{
	clear_ast(initial_symbol, minishell_variable);
	clear_ast(rest, minishell_variable);
	return (NULL);
}
