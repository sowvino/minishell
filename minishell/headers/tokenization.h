/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:40 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:39:40 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

// it starts from e_ not from _s because it's enumeration, not a structure
// i need to create tokens for echo, >, >>, && and so on
typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_APPEND,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_NEWLINE,
	TOKEN_IDENTIFIER,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// tokenization
t_token	*tokenization(t_minishell *minishell_variable);
t_token	*tokenization_handler(char *line, t_minishell *minishell_variable);

// separator
int		separator(char **line, t_token **token_list);
int		add_separator(t_token_type type, char **line, t_token **token_list);

// identifier
int		identifier(char **line, t_token **token_list,
			t_minishell *minishell_variable);
int		quotes_handler(char *tmp_line, size_t *i,
			t_minishell *minishell_variable);
bool	skip_quotes(char *line, size_t *i);
int		is_separator(char *s);

// utiels
t_token	*new_token(char *value, t_token_type type);
void	token_list_add_new(t_token **token_list, t_token *new_token);
void	clean_token_list(t_token **token_list);

#endif