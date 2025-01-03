/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-03 14:06:08 by selango           #+#    #+#             */
/*   Updated: 2025-01-03 14:06:08 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
/*This function redirection handling system checks the type of the input and then give the status of the input.*/
int redirect_exec_check(t_node *node)
{
    t_io_node *temp_list;
    int tmp_status;

    tmp_status =ENO_SUCCESS;
    temp_list = node->io_list;
    while(tmp_list)
    {
        if(temp_list->type == IO_OUT && 
                ft_output_redirect(temp_list,&tmp_status,false) != ENO_SUCCESS)// checks the output and gives the error code
            return(tmp_status);
        else if(temp_list->type == IO_IN &&
                    ft_input_redirect(temp_list,&tmp_status) != ENO_SUCCESS)//checks the input and gives the error code 
            return(tmp_status);
        else if(temp_list->type == IO_APPEND &&
                    ft_input_redirect(temp_list,&tmp_status,true) != ENO_SUCCESS)
            return(tmp_status);
        else if(temp_list->type == IO_HEREDOC)//here_document (<<) checks for the input and then stops until it finds the text.
        {
                dup2(temp_list->here_doc,0);//resets the text to 0. input is from the user
                close(temp_list->here_doc);// closes the here_doc 
        }
        temp_list = temp_list ->next;
    }    
    return(ENO_SUCCESS);
}
/*this functions resets to the default state*/

void ft_reset_state(bool pipe)
{
    if(pipe)
        return;
    dup2(minishell_global.ministdin,0);// resets to the default value
    dup2(minishell_global.ministdout,1);//resets to the default value
}
/*This function executes the child process by creating a new fork() and 
manages the error and looks for thge command path and then it executes the execve() command in it*/
static int child_execution(t_node *node)
{
    env_t_path path_status;//environment path status
    int temp_status;
    int fork_id;

    minishell_global.sigint_child = true;
    fork_id = fork();//forking the child process and parent
    if(!fork_id)// if child process is present
    {
        temp_status = redirect_exec_check(node);// this checks the input/output of the function and gives the success
        if(temp_status != ENO_SUCCESS)
            (ft_clear_msg(),exit(ENO_GENERAL));
        path_status = ft_get_exec_path(node->expanded_args[0]);
        if(path_status.error.no != ENO_SUCCESS)
        {
            temp_status = error_msg(path_status.error);
            (ft_clear_msg(),exit(temp_status));
        }
        if(execve(path_status.path,node->expanded_args,minishell_global) == -1)
            (ft_clear_msg(),exit(1));
    }
    waitpid(fork_id,&temp_status,0);//parent waits for the signal from the child.
    minishell_global.sigint_child = false;
    return(get_signal_status(temp_status));
}
/* This function handles the simple command execution */
int simple_cmd(t_node *node ,bool pipe)
{
    int temp_status;
    //if there is no arguments present in the terminal
    if(!node ->expanded_args)
    {
        temp_status = redirect_exec_check(node);
        ft_reset_state(pipe);
        return(temp_status && ENO_GENERAL);
    }
    //if the cmd is build_in_cmd it executes
    else if(default_checker(node->expanded_args[0]))
    {
        temp_status = redirect_exec_check(node);
        if(temp_status != ENO_SUCCESS)
        {
            ft_reset_state(pipe);
            return(ENO_SUCCESS);
        }
        temp_status = ft_default_exec(node->expanded_args);
        ft_reset_state(pipe);
        return(temp_status);if the
    }
    else
        return(child_execution(node));// It forks a child process to execute the command using execve, and returns the exit status.
}
