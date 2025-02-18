/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:37:37 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:37:37 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	if (minishell_variable->sigint_child) it correctly finishes 
// heredoc
// else 
// rl_replace_line("", 0) cleans the input string
// rl_on_new_line() tells that there is a new string
// rl_redisplay() shows changes
static void	sigint_handler(int num)
{
	t_minishell	*minishell_variable;

	(void)num;
	minishell_variable = get_minishell_variable();
	if (!minishell_variable)
	{
		ft_putstr_fd("\nError: minishell_variable is NULL\n", 2);
		return ;
	}
	if (minishell_variable->sigint_child)
	{
		ft_putstr_fd("\n", 1);
		minishell_variable->sigint_child = false;
		minishell_variable->heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// tcgetattr(STDIN_FILENO, &minishell_variable->terminal_settings) -
// current terminal settings. save it to minishell
// tcsetattr(STDIN_FILENO, TCSANOW, &terminal)
// change terminal bechaviour
// signal(SIGINT, sigint_handler) for "ctrl+c"
// signal(SIGQUIT, SIG_IGN) for "ctrl+\"
void	sig_init(t_minishell *minishell_variable)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &minishell_variable->terminal_settings) != 0)
	{
		perror("Error getting terminal attributes");
		return ;
	}
	terminal = minishell_variable->terminal_settings;
	terminal.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) != 0)
		perror("Error setting terminal attributes");
	minishell_variable->heredoc_sigint = false;
	minishell_variable->sigint_child = false;
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}

void	siquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}
