/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_io_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:46 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:46 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io_type	io_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (IO_IN);
	if (type == TOKEN_REDIR_OUT)
		return (IO_OUT);
	if (type == TOKEN_REDIR_HEREDOC)
		return (IO_HEREDOC);
	return (IO_APPEND);
}

t_io_node	*new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_io_node;

	new_io_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new_io_node)
		return (NULL);
	new_io_node->type = io_type(type);
	new_io_node->value = ft_strdup(value);
	if (!new_io_node->value)
	{
		free(new_io_node);
		return (NULL);
	}
	return (new_io_node);
}

void	append_io_node(t_io_node **list, t_io_node *new)
{
	t_io_node	*current_node;

	if (!(*list))
	{
		*list = new;
		return ;
	}
	current_node = *list;
	while (current_node && current_node->next)
		current_node = current_node->next;
	current_node->next = new;
}
