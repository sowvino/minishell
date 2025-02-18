/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  tree_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-03 18:25:06 by selango           #+#    #+#             */
/*   Updated: 2025-01-03 18:25:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function handles the signal of heredoc*/
void	heredoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\nHeredoc interrupted\n", 21);
		exit(1);
	}
}

/*This function handles here-document .if the document does
 not contain quotation then it expands the args
 or else it writes the string literals.
// this code init the signal for the heredocument
// assigns the value 		// checks if the delimiter
contains the quotation then while loop stops
// if the input finds the matches in the delimiter*/
void	heredoc_handler(t_io_node *io, int pfds[2],
		t_minishell *minishell_variable)
{
	char	*input;
	char	*quotation;

	quotation = io->value;
	signal(SIGINT, heredoc_signal_handler);
	while (*quotation && *quotation != '"' && *quotation != '\'')
		quotation++;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break ;
		if (found_delimiter(io->value, input))
			break ;
		if (!*quotation)
			ft_heredoc_expander(input, pfds[1], minishell_variable);
		else
		{
			ft_putstr_fd("Quit", 3);
			ft_putstr_fd("\n", 1);
		}
	}
	clean_minishell(minishell_variable);
	exit(0);
}

/*This function returns true if it is existed normally or else it returns false.
// In this when calling signal() ,WIFEXITED(*pid)
this checks if the signal is exited with a child process signal.
ft_sigquit is taken as the parameter of the call.WEXITSTATUS(*pid)
returns the value of the signal if it is exited normally. */
static bool	exit_leaf(int pfds[2], int *pid, t_minishell *minishell_variable)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, siquit_handler);
	minishell_variable->sigint_child = false;
	close(pfds[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

/*This function initialise the leaf of the tree. resolving the args expression .
expanding paths or file names for I/O operations.
// if the node has just args then
// todo// expand these args to expanded args
// creating a pipe .pfds[0]---> read,pfds[1]--->write.
// checks if it end of the leaf and returns the tree.*/
static void	init_leaf(t_node *node, t_minishell *minishell_variable)
{
	t_io_node	*io;
	int			pfds[2];
	int			pid;

	if (node->args)
		node->expanded_args = ft_expand(node->args, minishell_variable);
	io = node->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(pfds);
			minishell_variable->sigint_child = true;
			signal(SIGQUIT, SIG_IGN);
			pid = fork();
			if (!pid)
				heredoc_handler(io, pfds, minishell_variable);
			if (exit_leaf(pfds, &pid, minishell_variable))
				return ;
			io->here_doc = pfds[0];
		}
		else
			io->expanded_value = ft_expand(io->value, minishell_variable);
		io = io->next;
	}
}

/*this function used to initialize  the tree . This function calls
itself recursively for the right and left part of the tree*/
void	init_tree(t_node *node, t_minishell *minishell_variable)
{
	if (!node)
		return ;
	if (node->type == PIPE_NODE)
	{
		init_tree(node->left, minishell_variable);
		if (!minishell_variable->heredoc_sigint)
			init_tree(node->right, minishell_variable);
	}
	else
		init_leaf(node, minishell_variable);
}
