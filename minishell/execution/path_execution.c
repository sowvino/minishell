/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:30:52 by selango           #+#    #+#             */
/*   Updated: 2025/02/04 14:25:45 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_path	env_error(char *cmd, char *command_path, bool success)
{
	if (success)
		return ((t_env_path){(t_error){ENO_SUCCESS, 42, command_path},
			command_path});
	return ((t_env_path){(t_error){ENO_NOT_FOUND, ERR_CMD_NOT_FOUND, cmd},
		NULL});
}

/*this function has two parts it resolves and validates the executable paths*/

/* this function attempts  to find the executable cmd in directories
	it checks  and builds a executable path
	if executable path is found, it return the success and path
	if not found ,it returns the error msg*/
t_env_path	ft_env_path(char *path, char *cmd)
{
	size_t	i;
	t_error	error;
	char	*command_path;
	char	**split_path;

	i = 0;
	split_path = ft_split(path, ':');
	if (!path || !cmd || !split_path)
		return (env_error(cmd, NULL, false));
	while (split_path[i] != NULL)
	{
		command_path = ft_garbage_collector(\
		ft_strjoin_with_env(ft_strdup(split_path[i]), \
		ft_strdup(cmd), '/'), false);
		error = ft_exec_check(command_path, true);
		if (error.no == ENO_SUCCESS)
		{
			free_2d_array(split_path);
			return (env_error(cmd, command_path, true));
		}
		i++;
	}
	free_2d_array(split_path);
	return (env_error(cmd, NULL, false));
}
/*This function ft_get_exec_path is designed to find
 the path to a command (executable)*/

t_env_path	ft_get_exec_path(char *cmd, t_minishell *minishell_variable)
{
	char	*value;

	if (!cmd)
		return ((t_env_path){(t_error){ENO_NOT_FOUND, ERR_CMD_NOT_FOUND, cmd},
			NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		return ((t_env_path){ft_exec_check(cmd, false), cmd});
	}
	value = ft_search_envlist("PATH", minishell_variable);
	if (value)
	{
		return (ft_env_path(value, cmd));
	}
	return ((t_env_path){(t_error){ENO_NOT_FOUND, ERR_CMD_NOT_FOUND, cmd},
		NULL});
}
