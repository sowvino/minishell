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
in pipe structure .if dir is left then closes the read function and
duplicating the pfds[1] as stdout of the pipe
then it clos the pfds[1] i.e is the the write pipe. Then for
the right dirction the function is vice-versa.it then prints the status
and exist the status*/
static void	child_pipe_assign(t_node *node, int pfds[2],
		t_ast_direction direction, t_minishell *minishell_variable)
{
	int	status;

	if (direction == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (direction == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = ft_exec_branch(node, true, minishell_variable);
	clean_minishell(minishell_variable);
	exit(status);
}

/*this is used to interpret the status code returned by a child
process after it has exited.*/
int	get_signal_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

/*This function closes the pipe and gives the status of the pipe*/
static int	closing_pipe(int pfds[2], int *status, int pid,
		t_minishell *minishell_variable)
{
	close(pfds[0]);
	close(pfds[1]);
	waitpid(pid, status, 0);
	minishell_variable->sigint_child = false;
	return (get_signal_status(*status));
}

/*this function handles the execution connected via pipeline*/
static int	exec_pipe(t_node *tree, t_minishell *minishell_variable)
{
	int	status;
	int	pfds[2];
	int	pid_left;
	int	pid_right;

	status = 0;
	minishell_variable->sigint_child = true;
	pipe(pfds);
	pid_left = fork();
	if (!pid_left)
		child_pipe_assign(tree->left, pfds, TD_LEFT, minishell_variable);
	else
	{
		pid_right = fork();
		if (!pid_right)
			child_pipe_assign(tree->right, pfds, TD_RIGHT, minishell_variable);
		else
		{
			closing_pipe(pfds, &status, pid_left, minishell_variable);
			closing_pipe(pfds, &status, pid_right, minishell_variable);
		}
	}
	return (ENO_GENERAL);
}

/*this function recursively executes the commmand with a node of a tree*/
int	ft_exec_branch(t_node *tree, bool pipe, t_minishell *minishell_variable)
{
	if (!tree)
		return (1);
	if (tree->type == PIPE_NODE)
		return (exec_pipe(tree, minishell_variable));
	else
		return (simple_cmd(tree, pipe, minishell_variable));
	return (ENO_GENERAL);
}
