/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:36:58 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:36:58 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_initialization(char **env,
									t_minishell *minishell_variable)
{
	ft_memset(minishell_variable, 0, sizeof(t_minishell));
	minishell_variable->environment = env;
	envlist_initialization(minishell_variable);
	minishell_variable->ministdin = dup(0);
	minishell_variable->ministdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell_variable->terminal_settings);
}

static void	start_execution(t_minishell *minishell_variable)
{
	signal (SIGQUIT, siquit_handler);
	init_tree(minishell_variable-> ast, minishell_variable);
	if (minishell_variable-> heredoc_sigint)
	{
		clear_ast(&minishell_variable->ast, minishell_variable);
		minishell_variable->heredoc_sigint = false;
		return ;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &minishell_variable->terminal_settings);
	minishell_variable->exit_s = ft_exec_branch(minishell_variable->ast,
			false, minishell_variable);
	clear_ast(&minishell_variable->ast, minishell_variable);
	tcsetattr(STDIN_FILENO, TCSANOW, &minishell_variable->terminal_settings);
}

void	set_minishell_variable(t_minishell *new_minishell_variable)
{
	static t_minishell	*minishell_variable;

	minishell_variable = new_minishell_variable;
}
int	ft_is_all_spaces(char *str)
{
	int i = 0;

	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	set_line(t_minishell *minishell_variable)
{
	minishell_variable->line = readline("minishell: ");
	if (!minishell_variable->line)
	{
		clean_minishell(minishell_variable);
		ft_putstr_fd("exit\n", 1);
		exit(minishell_variable->exit_s);
	}
	if (ft_is_all_spaces(minishell_variable->line))
	{
		free(minishell_variable->line);
		minishell_variable->line = NULL;
		return;
	}
	if (minishell_variable->heredoc_sigint)
	{
		free(minishell_variable->line);
		minishell_variable->heredoc_sigint = false;
		return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell_variable;

	((void)argc, (void)argv);
	minishell_variable = ft_calloc(1, sizeof(t_minishell));
	set_minishell_variable(minishell_variable);
	minishell_initialization(env, minishell_variable);
	while (1)
	{
		sig_init(minishell_variable);
		set_line(minishell_variable);
		if (!minishell_variable->line)
    		continue;
		if (minishell_variable->line[0])
			add_history(minishell_variable->line);
		minishell_variable->tokens = tokenization(minishell_variable);
		if (!minishell_variable->tokens)
			free(minishell_variable->line);
		minishell_variable->ast = parsing(minishell_variable);
		if (minishell_variable->pars_error.type)
			parse_errors(minishell_variable);
		start_execution(minishell_variable);
	}
	ft_garbage_collector(NULL, true);
	return (clean_minishell(minishell_variable), minishell_variable->exit_s);
}
