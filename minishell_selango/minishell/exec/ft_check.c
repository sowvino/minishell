/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-30 15:39:49 by selango           #+#    #+#             */
/*   Updated: 2024-12-30 15:39:49 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*The access() function is used to check whether the calling process can access a file in a 
specified way (e.g., for reading, writing, or executing).*/
t_error ft_exec_check(char *file,bool cmd)
{
    if(!file)
        return((t_error){ENO_GENERAL,NO_SUCH_FILE,file});
    if(access(file,F_Ok) == 0)
    {
        if(access(file,X_OK) == -1)
            return ((t_error){ENO_CANT_EXEC,PERMISSSION_DENIED,file});
        return((t_error){ENO_SUCCESS,0,NULL});
    }
    if(cmd)//flag is present to indicate user is searching for cmd or file.
        return((t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,file});
    return((t_error){ENO_NOT_FOUND,NO_SUCH_FILE,file});
}
/*this function checks if the file is readable or not and displays error msg accordingly*/
t_error ft_read_check(char *file)
{
    if(!file)
        return((t_error){ENO_GENERAL,NO_SUCH_FILE,file});
    if(access(file,F_Ok)== 0)
    {
        if(access(file,R_OK == -1))
             return ((t_error){ENO_CANT_EXEC,PERMISSSION_DENIED,file});
        return((t_error){ENO_SUCCESS,0,NULL});
    }
    return((t_error){ENO_NOT_FOUND,NO_SUCH_FILE,file});
}
/*this function checks if the file is writable or not and displays the error msg accordinly*/
t_error ft_write_check(char *file)
{
    if(!file)
        return((t_error){ENO_GENERAL,NO_SUCH_FILE,file});
       if(access(file,F_Ok)== 0)
    {
        if(access(file,W_OK == -1))
             return ((t_error){ENO_CANT_EXEC,PERMISSSION_DENIED,file});
        return((t_error){ENO_SUCCESS,0,NULL});
    }
    return((t_error){ENO_NOT_FOUND,NO_SUCH_FILE,file});
}

