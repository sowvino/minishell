/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-21 12:29:23 by selango           #+#    #+#             */
/*   Updated: 2025-01-21 12:29:23 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this fn search the key env variable in the
env var list and returns its val or it returns NULL value */
char	*ft_search_envlist(char *key, t_minishell *minishell_variable)
{
	t_env	*envlist;

	if (!key)
	{
		printf("Error: NULL key provided to ft_search_envlist\n");
		return (NULL);
	}
	envlist = minishell_variable->envlist;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
			return (envlist->value);
		envlist = envlist->next;
	}
	return (NULL);
}

int	error_msg(char *err_msg)
{
	printf("minishell:cd:'%s:No such file or directory\n", err_msg);
	return (1);
}

int	ft_str_isdigit(const char *str)
{
	if (!str || *str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}
