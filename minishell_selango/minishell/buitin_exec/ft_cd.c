/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-14 13:42:45 by selango           #+#    #+#             */
/*   Updated: 2024-11-14 13:42:45 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*this fn gives the home of the working directory*/
static int ft_home(void)
{
    char *home;
    envlist_updating("OLDPWD",ft_search_envlist("PWD"),false);
    home = ft_search_envlist("HOME");
    if(!home)
    {
        ft_putstr_fd("Home not found\n",2);
        return(1);
    }
    if (chdir(home) == 1)//change directory inbuilt cmds in c
    {
        envlist_updating("PWD",home,false);
        return(0);
    }
    return(1);
}
/*this fn replicates how cd fn works properly
it changes the path and also updates the envlist */
int ft_cd(char *path)
{
    if(!path)
        return(ft_home());
    if(chdir(path) != 0)
        return(cd_error_msg(path));
    envlist_updating("OLDPWD",ft_search_envlist("PWD"),false);
    return(ft_pwd());
}
