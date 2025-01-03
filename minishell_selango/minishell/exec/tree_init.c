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
#include "parsing/parsing.h"



/*This function initialise the leaf of the tree*/
static void init_leaf(t_node *node)
{
    t_io_node *io;
    int pfds[2];
    int pid;

    if(node->args)
        node->expanded_args = ft_expand(node->args);//todo
    io = node->io_list;
    while(io)
    {
        if(io->type == IO_HEREDOC)
        {
            pipe(pfds);
            minishell_global.sigint_child = true;
            pid = (signal(SIGQUIT,SIG_IGN));
            pid = fork();
            if(!pid)
                heredoc_handler(io,pfds);//todo
            if(exit_leaf(pfds,&pid))
                return;
            io->here_doc = pfds[0];
        }
        else
            io->expanded_value =ft_expand(io->value);//todo
        io = io->next;
    }
}

/*this function used to initialize  the tree . This function calls itself recursively for the right and left part of
the tree*/
void init_tree(t_node *node)
{
    if(!node)
        return;
    if(node->type == PIPE_NODE || 
        node->type == AND_NODE || node->type == OR_NODE)
    {
        init_tree(node->left);
        if(!minishell_global.heredoc_sigint)
            init_tree(node->right);
    }
    else    
        init_leaf(node);//todo
}
