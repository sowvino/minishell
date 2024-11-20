/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 13:45:54 by selango           #+#    #+#             */
/*   Updated: 2024-11-20 13:45:54 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn updates and remove the key from the envlist.*/
static void ft_unset_utilis(char *key)
{
    t_env *curr;
    t_env *prev;

    prev = NULL;
    curr = minishell_global.envlist;
    while(curr)
    {
        if(!ft_strcmp(key,curr->key))
        {
           if(prev)
                prev->next = curr->next;
           else
                minishell.global.envlist = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr =curr->next;
    }
}
/*this fn unset the value of key given if it matches to the curr value . */
int ft_unset(char **argv)
{
    int i ;
    i =1;
    if(!argv[1])
        return(0);
    
    while(argv[i])
    {
        if(!ft_valid(argv[i]))
           int error_msg(argv[i]);//prints the error msg
        else
            ft_unset_utilis(ft_garbage_collector(set_key(argv[i]),false));// remove the list from envlist
        i++;
    }
    return(0);
}
