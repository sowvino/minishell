/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 11:39:47 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 11:39:47 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn gives the current working directory of the system*/
int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	envlist_updating("PWD", cwd, false);
	return (0);
}
