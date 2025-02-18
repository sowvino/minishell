/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025-01-21 13:42:22 by selango           #+#    #+#             */
/*   Updated: 2025-01-21 13:42:22 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn is used to export the list ,if the arr exists
	then it checks if it arr-> val is not null,
	and key does not contain _ _ is usually exists in env_variable and
	starts it with quotes(declare -x PATH="/usr/bin:/bin"declare
	-x HOME="/home/user") and it ends with double quote and newline.
	if it contain $ in the beginning then it prints "\" in it
	and then the value is printed  likewise the export list is printed*/
static void	list_export(t_minishell *minishell_variable)
{
	t_env	*array;
	size_t	i;

	array = minishell_variable->envlist;
	while (array)
	{
		if (array->value != NULL && (ft_strcmp(array->key, "_") != 0))
		{
			printf("declare -x %s =\"", array->key);
			i = 0;
			while ((array->value)[i])
			{
				if ((array->value)[i] == '$' || (array->value)[i] == '"')
					printf("\\%c", (array->value)[i++]);
				else
					printf("%c", (array->value)[i++]);
			}
			printf("\"\n");
		}
		else if (array->value == NULL && (ft_strcmp(array->key, "_") != 0))
			printf("declare -x %s\n", array->key);
		array = array->next;
	}
}

/*checks whether the key is valid are not if not it return(0) ,
	else return(1)*/
int	ft_valid(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_export_err_msg(char *id)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid id\n", 2);
	return (1);
}

void	export_update(char *key, char *s, t_minishell *minishell_variable)
{
	if (ft_search_envlist(key, minishell_variable))
		envlist_updating(key, s, false, minishell_variable);
	else
		envlist_updating(key, s, true, minishell_variable);
}

/*this fn exports val and key given to env. argv[1] == NUll then it
	prints all the previous exports fn.if(argv[1]) thn it checks if
	it is a valid key if yes thn,it extract key and values.
	update the env list and exit */
int	ft_export(char **argv, t_minishell *minishell_variable)
{
	int		i;
	int		exit_no;
	char	*key;

	i = 1;
	exit_no = 0;
	if (!argv[1])
	{
		list_export(minishell_variable);
		return (0);
	}
	while (argv[i])
	{
		if (ft_valid(argv[i]) == 0)
			exit_no = ft_export_err_msg(argv[i]);
		else
		{
			key = set_key(argv[i]);
			export_update(key, set_value(argv[i]), minishell_variable);
		}
		i++;
	}
	return (exit_no);
}
