/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 13:55:54 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 13:55:54 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_error_msg(t_error err)
{
    if(err.msg == ERR_CMD_NOT_FOUND)
        return(printf("minishell: %s : command not found\n",err.report),err.no);
    else if(err.msg == ERR_NO_SUCH_FILE)
    
        return(printf("minishell:%s:No such file or directory\n",err.report),err.no);
    else if(err.msg == ERR_PERMISSION_DENIED)
        return(printf("minishell: %s: Permission denied\n",err.report),err.no);
    else if(err.msg == ERR_UNCLEAR)
        return(printf("Minishell : %s : unclear error\n",err.report),err.no);
    else if(err.msg == ERR_TOO_MANY_ARGUMENTS)
        return(printf("Minishell: exit too many arguments\n"),err.no);
    else if(err.msg == ERR_NUMERIC_REQUIRED)
        return(printf("Minishell :exit: %s : numeric argument required",err.report),err.no);
    return(0);
}
