/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-30 17:05:31 by selango           #+#    #+#             */
/*   Updated: 2024-12-30 17:05:31 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*This function assigns the write and read mode to the child and parent 
in pipe structure .if dir is left then closes the read function and duplicating the pfds[1] as stdout of the pipe
then it clos the pfds[1] i.e is the the write pipe. Then for the right dirction the function is vice-versa.it then prints the status and exist the status*/
static void child_pipe_assign(t_node *node,int pfds[2],t_ast_direction direction)
{
    int status;
    if(direction == TD_LEFT)
    {
        close (pfds[0]);
        dup2(pfds[1],STDOUT_FILENO);
        close(pfds[1]);
    }
    else if(direction == TD_RIGHT)
    {
        close(pfds[1]);
        dup2(pfds[0],STDIN_FILENO);
        close(pfds[0]);
    }
    status = ft_exec_node(node,true);
    ft_clear_msg();//clear the message using the fn
    exist(status);
}
/*this is used to interpret the status code returned by a child process after it has exited.*/
int get_signal_status(int status)
{
    if(WIFSIGNALED(status))
        return(128 + WTERMSIG(status));
    return(WEXITSTATUS(status));
}
