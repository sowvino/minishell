/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:10 by mklimuk           #+#    #+#             */
/*   Updated: 2025/01/20 16:29:21 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_err(char **token_descriptions, t_token_type token_type)
{
	ft_putstr_fd("Syntax error: unexpected token `", 2);
	ft_putstr_fd(token_descriptions[token_type], 2);
	ft_putstr_fd("'\n", 2);
}

void	parse_errors(t_minishell *minishell_variable)
{
	t_pars_error_type	type;
	t_token_type		token_type;
	char				**token_descriptions;

	(void) token_type;
	token_descriptions = (char *[]){"TOKEN_IDENTIFIER",
		"<", ">", "<<", ">>", "|", "(", ")", "newline"};
	type = minishell_variable->pars_error.type;
	if (!type)
		return ;
	if (type == SYNTAX_ERROR)
	{
		if (!minishell_variable->current_token)
			token_type = TOKEN_NEWLINE;
		else
			token_type = minishell_variable->current_token->type;
		if (token_type < 0 || token_type
			>= (sizeof(token_descriptions) / sizeof(token_descriptions[0])))
			ft_putstr_fd("Syntax error: unknown token\n", 2);
		else
			put_err(token_descriptions, token_type);
		minishell_variable->exit_s = 258;
	}
	clear_ast(&minishell_variable->ast, minishell_variable);
	ft_bzero(&minishell_variable->pars_error, sizeof(t_pars_error));
}
