/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:02 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:02 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_node_type
{
	PIPE_NODE,
	CMD_NODE
}	t_node_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	struct s_io_node	*prev;
	struct s_io_node	*next;
	int					here_doc;
}	t_io_node;

typedef struct s_node
{
	char			*args;
	char			**expanded_args;
	struct s_node	*left;
	struct s_node	*right;
	t_node_type		type;
	t_io_node		*io_list;
}	t_node;

// there are two types of mistakes: wirh memoty and syntax
// why MEM_ERROR is 1: it need because of condition 
// in (minishell_global.pars_error.type).0 means that there are no errors
// SYNTAX_ERROR will be automatically = 2
typedef enum e_pars_error_type
{
	MEM_ERROR = 1,
	SYNTAX_ERROR
}	t_pars_error_type;

// information about parsing errors
// str is for information about error
// type is a type of error
typedef struct s_pars_error
{
	char				*str;
	t_pars_error_type	type;
}	t_pars_error;

// parser builders
int			build_io_list(t_io_node **io_list, t_minishell *minishell_variable);
t_node		*build_command(t_minishell *minishell_variable);
int			build_identifiers_list(char **args,
				t_minishell *minishell_variable);

// nodes
t_node		*new_node(t_node_type type);
t_node_type	node_type(void);

// checkers
int			is_binary_operation(t_minishell *minishell_variable);
int			is_redirectory(t_token_type type);

// cleaners
void		free_2d_array(char **two_d_array);
void		free_3d_array(char ***three_d_array);
void		clear_io_list(t_io_node **lst);
void		clear_cmd_node(t_node *node);
void		recursive_clear_cmd(t_node *node);
void		clear_ast(t_node **ast, t_minishell *minishell_variable);
t_node		*clear_i_s(t_node **initial_symbol,
				t_node **rest, t_minishell *minishell_variable);

// io_nodes
t_io_type	io_type(t_token_type type);
t_io_node	*new_io_node(t_token_type type, char *value);
void		append_io_node(t_io_node **list, t_io_node *new);

// utils
// int			current_priority(t_minishell *minishell_variable);
int			priority(void);
t_node		*handle_round_paren(t_minishell *minishell_variable);
int			handle_command_token(t_node *node, t_minishell *minishell_variable);

// parsing
t_node		*term(t_minishell *minishell_variable);
t_node		*build_ast(int min_priority, t_minishell *minishell_variable);
t_node		*build_ast_node(t_node *initial_symbol,
				t_node *rest, t_minishell *minishell_variable);
t_node		*parsing(t_minishell *minishell_variable);

// errors
void		parse_errors(t_minishell	*minishell_variable);

#endif
