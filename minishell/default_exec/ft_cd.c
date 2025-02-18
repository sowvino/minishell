/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-17 14:21:28 by selango           #+#    #+#             */
/*   Updated: 2025-01-17 14:21:28 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn gives the home of the working directory*/
static int	ft_home(t_minishell *minishell_variable)
{
	char	*home;

	envlist_updating("OLDPWD", ft_search_envlist("PWD", minishell_variable),
		false, minishell_variable);
	home = ft_search_envlist("HOME", minishell_variable);
	if (!home)
	{
		ft_putstr_fd("Home not found\n", 2);
		return (1);
	}
	if (chdir(home) == ENO_SUCCESS)
	{
		envlist_updating("PWD", home, false, minishell_variable);
		return (0);
	}
	return (1);
}

/*this fn replicates how cd fn works properly
it changes the path and also updates the envlist */
int	ft_cd(char *path, t_minishell *minishell_variable)
{
	if (!path)
		return (ft_home(minishell_variable));
	if (chdir(path) != ENO_SUCCESS)
		return (error_msg(path));
	envlist_updating("OLDPWD", ft_search_envlist("PWD", minishell_variable),
		false, minishell_variable);
	return (0);
}
