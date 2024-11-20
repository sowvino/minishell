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
static void ft_free_list(void)
{
    t_env *envlist;
    t_env *envlist_toclear;

    envlist = minishell_global.envlist;
    while(envlist)
    {
        envlist_toclear = envlist;
        envlist = envlist->next;
        free(envlist_toclear);
    }
    minishell_global.envlist = NULL;
}
void ft_clear_msg()
{
    ft_garbage_collector(NULL,true);
    ft_clear_ast(&g_minishell.ast);//to be done
    ft_freee_list();
    rl_clear_history();// to be done
    tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);//to be done
}