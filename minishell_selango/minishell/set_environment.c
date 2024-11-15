/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 14:48:39 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 14:48:39 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// THE CODE SETS ENVIRONMENT. IT SETS AND STORES ENVIRONMENT VARIABLES.
// we need ENVIRONMENT VARIABLES because they contains information about the system. for example we might need to know some path.
// it's more for execution processes

// we need a garbage container or we'll get memory leaks. because we take memory for ft_strdup,
	//ft_substr and so on
// but we are not cleaning memory after usage. so we have to write agarbage container

// need to add a garbage collector!!!
char	*set_key(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i)));
		i++;
	}
	return (ft_strdup(str));
}

// need to add a garbage collector!!!
char	*set_value(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, i, ft_strlen(str) - i));
	}
	return (NULL);
}

// need to add a garbage collector!!!
// the function creates new envlist-element from key and value.
static t_env	*new_envlst(char *key, char *value)
{
	t_env *new_element;
	new_element = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_element)
		return (NULL);
	new_element->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new_element->value = ft_garbage_collector(ft_strdup(value));
	new_element->next = NULL;
	return (new_element);
}
// here we are taking minishell enbironment variables and parsing them to key and value. also updating the list envlist.
// the difference is that environment variable is a massive of strings,
//but envlist variable is a list with keys and values.
void	envlist_initialization(void)
{
	char **environment;
	int i;
	char *key;
	char *value;

	environment = minishell_global.environment;
	if (!environment)
		return ;
	i = 0;
	while (environment[i])
	{
		key = set_key(environment[i]);
		value = set_value(environment[i]);
		envlist_updating(key, value, true);
		i++;
	}
}
int	ft_env(void)
{
	t_env *list;
	list = minishell_global.envlist;
	while (list)
	{
		if (list->value)
			printf("%s = %s \n", list->key, list->value);
		list = list->next;
	}
	return (1);
}
