/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-24 17:08:53 by selango           #+#    #+#             */
/*   Updated: 2024-12-24 17:08:53 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fn first checks if the builtin functions are matched else it returns false value*/
bool checker(char **argv)
{
    char *str;
    
    str = argv[0];
    if(!argv)
        return(false);
    else if(!ft_strcmp(str,"echo") ||
     !ft_strcmp(str,"exit")||!ft(strcmp(str,"cd"))||
     !ft_strcmp(str,"pwd")||!ft_strcmp(str,"export")|| !ft_strcmp(str,"unset") || !ft_strcmp(str,"env"))
        return(true);
    return (false);  
}
/*It checks whether given argv consists of builtin fn if yes , then it executes the responding functions */
int ft_default_exec(int argc,char **argv)
{
    char *str ;

    str = argv[0];
    if(ft_strcmp(str,"echo") == 0)
        return(ft_echo(argv));
    else if(ft_strcmp(str,"cd") == 0)
        return(ft_cd(argv[1]));
    else if(ft_strcmp(str,"pwd") == 0)
        return(ft_pwd());
    else if(ft_strcmp(str,"env") == 0)
        return(ft_env());
    else if(ft_strcmp(str,"export") == 0) 
        return(ft_export(argv));
    else if(ft_strcmp(str,"unset") == 0)
        return(ft_unset(argv));
    ft_exit(argv);
    return(ENO_GENERAL);   
}
