/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-14 13:52:32 by selango           #+#    #+#             */
/*   Updated: 2024-11-14 13:52:32 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this fn search the key env variable in the env var list and returns its val or it returns NULL value */
char *ft_search_envlist(char *key)
{
    t_env *envlist;
    envlist = minishell_global.envlist;
    while(envlist)
    {
        if(!ft_strcmp(key,envlist->key))
            return(envlist->value)
        envlist = envlist->next;
    }
    return(NULL);
}
static int cd_error_msg(char *err_msg)
{
    printf("minishell:cd:'%s:No such file or directory\n",err_msg);
    return(1);
}
