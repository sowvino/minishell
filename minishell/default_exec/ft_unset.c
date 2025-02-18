/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-17 14:49:40 by selango           #+#    #+#             */
/*   Updated: 2025-01-17 14:49:40 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn updates and remove the key from the envlist.*/
static void	ft_unset_utilis(char *key, t_minishell *minishell_variable)
{
	t_env	*curr;
	t_env	*prev;

	prev = NULL;
	curr = minishell_variable->envlist;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			if (prev)
				prev->next = curr->next;
			else
				minishell_variable->envlist = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/*this fn unset the value of key given if it matches to the curr value . */
int	ft_unset(char **argv, t_minishell *minishell_variable)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (!ft_valid(argv[i]))
			error_msg(argv[i]);
		else
			ft_unset_utilis(ft_garbage_collector(set_key(argv[i]), false),
				minishell_variable);
		i++;
	}
	return (0);
}
