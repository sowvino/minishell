/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:10:19 by mklimuk           #+#    #+#             */
/*   Updated: 2025/02/10 12:56:02 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_envlst(char *key, char *value)
{
	t_env	*new_element;

	new_element = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_element)
		return (NULL);
	new_element->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new_element->value = ft_garbage_collector(ft_strdup(value), false);
	new_element->next = NULL;
	return (new_element);
}

// the function adding new element key-value to the end of envlist.
// if the list doesn't exist, it crates the new one
// or while current is not the last, it moves.
//  and when we got the last element of the list it adds new elenet to the end.
void	envlist_add_to_back(t_env *new, t_minishell *minishell_variable)
{
	t_env	*curr;

	if (!minishell_variable->envlist)
	{
		minishell_variable->envlist = new;
		return ;
	}
	curr = minishell_variable->envlist;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

t_minishell	*get_minishell_variable(void)
{
	static t_minishell	*minishell_variable = NULL;

	if (minishell_variable == NULL)
		minishell_variable = ft_calloc(1, sizeof(t_minishell));
	return (minishell_variable);
}
