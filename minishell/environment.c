/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:37:25 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:37:25 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*set_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_collector
				(ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

// need to add a garbage collector!!!
// the function is adding or updating elements in envlist.
// if flag is true, key and value will be added to the
// envlist because
// it means that they are not exist in the envlist.
// "while(envlist)"-loop and if(!ft_strcmp...)-condition :
// they are about changing key's value if we want to change it.
// if there is no such a key in the envlist and the flag is true,
// function will add key and value to the end of the list.
void	envlist_updating(char *key, char *value,
							bool flag, t_minishell *minishell_variable)
{
	t_env	*envlist;

	envlist = minishell_variable->envlist;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
		{
			if (value)
				envlist->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		envlist = envlist->next;
	}
	if (flag)
		envlist_add_to_back(new_envlst(key, value), minishell_variable);
}

void	envlist_initialization(t_minishell *minishell_variable)
{
	char	**environment;
	int		i;
	char	*key;
	char	*value;

	environment = minishell_variable->environment;
	if (!environment)
		return ;
	i = 0;
	while (environment[i])
	{
		key = set_key(environment[i]);
		value = set_value(environment[i]);
		envlist_updating(key, value, true, minishell_variable);
		i++;
	}
}

int	ft_env(t_minishell *minishell_variable)
{
	t_env	*list;

	list = minishell_variable->envlist;
	while (list)
	{
		if (list->value != NULL)
			printf("%s = %s \n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}
