/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 14:50:36 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 14:50:36 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clears the envlist and free the list*/
static void ft_clear_envlist(void)
{
    t_env *envlist;
    t_env *envlist_tofree;

    envlist = minishell_global.envlist;
    while(envlist)
    {
        envlist_tofree = envlist;
        envlist = envlist->next;
        free(envlist_tofree);
    }
    minishell_global.envlist = NULL;
}
