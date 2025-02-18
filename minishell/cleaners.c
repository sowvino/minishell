/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-13 13:19:27 by selango           #+#    #+#             */
/*   Updated: 2025-02-13 13:19:27 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	envlist_cleaner(t_minishell *minishell_variable)
{
	t_env	*envlist;
	t_env	*envlist_to_free;

	envlist = minishell_variable->envlist;
	while (envlist)
	{
		envlist_to_free = envlist;
		envlist = envlist->next;
		free(envlist_to_free);
	}
	minishell_variable->envlist = NULL;
}

void	clean_minishell(t_minishell *minishell_variable)
{
	ft_garbage_collector(NULL, true);
	clear_ast(&minishell_variable->ast, minishell_variable);
	envlist_cleaner(minishell_variable);
	rl_clear_history();
	if (minishell_variable->ministdin > 2)
		close(minishell_variable->ministdin);
	if (minishell_variable->ministdout > 2)
		close(minishell_variable->ministdout);
	tcsetattr(STDIN_FILENO, TCSANOW, &minishell_variable->terminal_settings);
}

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}
