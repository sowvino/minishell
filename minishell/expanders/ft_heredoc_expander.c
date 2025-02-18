/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_expander.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:32:11 by selango           #+#    #+#             */
/*   Updated: 2025/02/10 17:50:59 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this function handles how to handle if the str contains $?*/
static int	heredoc_writer(char *str, size_t i, int fd,
		t_minishell *minishell_variable)
{
	size_t	begin;
	char	*temp;

	begin = i++;
	if (str[i] == '?')
	{
		return (ft_putnbr_fd(minishell_variable->exit_s, fd), 2);
		return (2);
	}
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (begin != i)
	{
		temp = ft_garbage_collector(ft_substr(str, begin, i), false);
		temp = ft_search_envlist(str, minishell_variable);
		if (temp)
			ft_putstr_fd(str, fd);
	}
	return (i);
}

/*This function handles the expansion of the args if the $ sign is present or
 else it prints the string literals*/
void	ft_heredoc_expander(char *input,
		int fd, t_minishell *minishell_variable)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i += heredoc_writer(input, i, fd, minishell_variable);
		}
		else
		{
			ft_putchar_fd(input[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}
