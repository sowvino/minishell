/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:06:08 by selango           #+#    #+#             */
/*   Updated: 2025/02/11 18:35:29 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdio.h>

/*This function redirection handling system checks the type
of the input and then give the status of the input.
// checks the output and gives the error code
//checks the input and gives the error code
//here_document (<<) checks for the input and then stops until it finds the text.
//resets the text to 0. input is from the user
// closes the here_doc */
int	redirect_exec_check(t_node *node)
{
	t_io_node	*temp_list;
	int			tmp_status;

	tmp_status = ENO_SUCCESS;
	temp_list = node->io_list;
	while (temp_list)
	{
		if (temp_list->type == IO_APPEND && ft_append_redirect(temp_list,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (temp_list->type == IO_OUT && ft_output_redirect(temp_list,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (temp_list->type == IO_IN && ft_input_redirect(temp_list,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (temp_list->type == IO_HEREDOC)
		{
			dup2(temp_list->here_doc, 0);
			close(temp_list->here_doc);
		}
		temp_list = temp_list->next;
	}
	return (ENO_SUCCESS);
}
/*this functions resets to the default state
// resets to the default value
//resets to the default value*/

void	ft_reset_state(bool pipe, t_minishell *minishell_variable)
{
	if (pipe)
		return ;
	dup2(minishell_variable->ministdin, 0);
	dup2(minishell_variable->ministdout, 1);
}

/*This function executes the child process by creating a new fork() and
manages the error and looks for thge command path and
then it executes the	execve(void) command in it
//environment path status.//forking the child process and parent.
// if child process is present.//
this checks the input/output of the function and gives the success
//parent waits for the signal from the child.*/
static int	child_execution(t_node *node, t_minishell *minishell_variable)
{
	t_env_path	path_status;
	int			temp_status;
	int			fork_id;

	minishell_variable->sigint_child = true;
	fork_id = fork();
	if (fork_id == 0)
	{
		temp_status = redirect_exec_check(node);
		if (temp_status != ENO_SUCCESS)
			(clean_minishell(minishell_variable), exit(ENO_GENERAL));
		path_status = ft_get_exec_path(node->expanded_args[0],
				minishell_variable);
		if (path_status.error.no != ENO_SUCCESS)
		{
			temp_status = ft_error_msg(path_status.error);
			(clean_minishell(minishell_variable), exit(temp_status));
		}
		if (execve(path_status.path, node->expanded_args,
				minishell_variable->environment) == -1)
			(clean_minishell(minishell_variable), exit(1));
	}
	waitpid(fork_id, &temp_status, 0);
	minishell_variable->sigint_child = false;
	return (get_signal_status(temp_status));
}

/* This function handles the simple command execution
 //if there is no arguments present in the terminal
   //if the cmd is build_in_cmd it executes
   // It forks a child process to execute the command using execve,
	and returns the exit status. */
int	simple_cmd(t_node *node, bool pipe, t_minishell *minishell_variable)
{
	int	temp_status;

	if (!node->expanded_args)
	{
		temp_status = redirect_exec_check(node);
		ft_reset_state(pipe, minishell_variable);
		return (temp_status && ENO_GENERAL);
	}
	else if (default_checker(&node->expanded_args[0]))
	{
		temp_status = redirect_exec_check(node);
		if (temp_status != ENO_SUCCESS)
		{
			ft_reset_state(pipe, minishell_variable);
			return (ENO_SUCCESS);
		}
		temp_status = ft_default_exec(node->expanded_args, minishell_variable);
		ft_reset_state(pipe, minishell_variable);
		return (temp_status);
	}
	else
	{
		ft_reset_state(pipe, minishell_variable);
		return (child_execution(node, minishell_variable));
	}
}
