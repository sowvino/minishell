/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-17 14:40:00 by selango           #+#    #+#             */
/*   Updated: 2025-01-17 14:40:00 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*skip the spaces if any and then checks the sign
	- if yes then it reassign sign to -1*/
static void	skip_spaces(char *s, int *i, int *sign)
{
	if (!s)
		return ;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}
/*this fn checks if it is number,
	if not it prints err_msg from exec else converts the str_literal to number*/

void	err_msg(char *str, t_minishell *minishell_variable)
{
	int		i;
	int		exit_str;
	t_error	error_data;

	exit_str = minishell_variable->exit_s;
	error_data.no = ENO_EXEC_ERROR;
	error_data.msg = ERR_NUMERIC_REQUIRED;
	error_data.report = str;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0' || (!ft_isdigit((str[i])) || str[i] != '-'
			|| str[i] != '+'))
	{
		exit_str = ft_error_msg(error_data);
		(clean_minishell(minishell_variable), exit(exit_str));
	}
}

void	error_init(char *str, t_minishell *minishell_variable)
{
	t_error	error_data;

	error_data.no = ENO_EXEC_ERROR;
	error_data.msg = ERR_NUMERIC_REQUIRED;
	error_data.report = str;
	minishell_variable->exit_s = ft_error_msg(error_data);
	clean_minishell(minishell_variable);
	exit(minishell_variable->exit_s);
}

static int	atoi_exit(char *str, t_minishell *minishell_variable)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	skip_spaces(str, &i, &sign);
	if (!str)
		error_init(str, minishell_variable);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error_init(str, minishell_variable);
		result = (result * 10) + (str[i] - '0');
		if (result > LONG_MAX)
			error_init(str, minishell_variable);
		i++;
	}
	return ((result * sign) % 256);
}

/*this fn exit the terminal example,if argv[0] is exit status of
the shell,else if it finds more argv
then it displays err_msg too many arguments,else if
it has only one argv[2] then it converts str to atoi_exists.*/
void	ft_exit(char **argv, t_minishell *minishell_variable)
{
	int		exit_s;
	t_error	error_data;

	exit_s = minishell_variable->exit_s;
	error_data.no = ENO_EXEC_ERROR;
	error_data.report = NULL;
	if (argv[1] && (!ft_strcmp(argv[1], "*") || argv[2]))
	{
		error_data.msg = ERR_TOO_MANY_ARGUMENTS;
		exit_s = ft_error_msg(error_data);
		(clean_minishell(minishell_variable), exit(exit_s));
	}
	else if (argv[1])
		exit_s = atoi_exit(argv[1], minishell_variable);
	else
		exit_s = 0;
	clean_minishell(minishell_variable);
	exit(exit_s);
}
