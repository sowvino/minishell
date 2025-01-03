/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-02 16:39:17 by selango           #+#    #+#             */
/*   Updated: 2025-01-02 16:39:17 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"

/*This function helps to redirect the output as the input of another function handles both the > or >> functions in it.*/
int ft_output_redirect(t_io_node *io_list,int * status,bool is_append)
{
    int fd;
    int flags;

    if(!io_list->expanded_value || io_list->expanded_value[1])//checks if it does not contain any expanded_value 
    {
        *status = ft_error_msg((t_error) {ENO_GENERAL,ERR_UNCLEAR,io_list->value});
        return(*status);
    }
    flags = O_CREAT | O_WRONLY;
    if(is_append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open (io_list->expanded_value[0],flags,0644);//open the first value,create if it doesnt exists, write the text, permission for the read and write the data.
    if (fd == -1)// if fd fails then print the error_status
    {
        *status = ft_error_msg(ft_write_check(io_list->expanded_value[0]));
        return(*status);
    }
    dup2(fd,STDOUT_FILENO);// copies the fd to stdout_fileno.
    close(fd);
    *status = 0;
    return(*status);
}

/*This function is to handle the input redirection .It ensures that the input file is valid, opens it for reading*/
int ft_input_redirect(t_io_node *io_list,int *status)
{
    int fd ;
    if(!io_list->expanded_value || io_list->expanded_value[1])//
    {
        *status = ft_error_msg((t_error){ENO_GENERAL,ERR_UNCLEAR,io_list->value});
        return(*status);
    }
    fd = open(io_list->expanded_value[0],O_RDONLY);
    if(fd ==-1)
    {
        *status = ft_error_msg(ft_read_check(io_list->expanded_value[0]));//checks for the read permission
        return(*status);
    }
    dup2(fd,STDIN_FILENO);//copies the fd to stdin_fileno
    close(fd);
    *status = 0;
    return(*status);
}
