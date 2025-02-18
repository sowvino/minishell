/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-17 14:55:09 by selango           #+#    #+#             */
/*   Updated: 2025-01-17 14:55:09 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_msg(t_error err)
{
	if (err.msg == ERR_CMD_NOT_FOUND)
		return (printf("minishell: %s : command not found\n", err.report),
			err.no);
	else if (err.msg == ERR_NO_SUCH_FILE)
		return (printf("minishell:%s:No such file or directory\n", err.report),
			err.no);
	else if (err.msg == ERR_PERMISSION_DENIED)
		return (printf("minishell: %s: Permission denied\n", err.report),
			err.no);
	else if (err.msg == ERR_UNCLEAR)
		return (printf("minishell : %s : unclear error\n", err.report),
			err.no);
	else if (err.msg == ERR_TOO_MANY_ARGUMENTS)
		return (printf("minishell: exit: too many arguments\n"), err.no);
	else if (err.msg == ERR_NUMERIC_REQUIRED)
		return (printf("exit: %s : numeric argument required",
				err.report), err.no);
	return (0);
}

/*this fn first checks if the builtin 
functions are matched else it returns false value*/
bool	default_checker(char **argv)
{
	char	*str;

	str = argv[0];
	if (!argv)
		return (false);
	else if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "exit")
		|| (!ft_strcmp(str, "cd")) || (!ft_strcmp(str, "pwd"))
		|| (!ft_strcmp(str, "export")) || (!ft_strcmp(str, "unset"))
		|| (!ft_strcmp(str, "env")))
		return (true);
	return (false);
}

/*It checks whether given argv consists of builtin fn if yes ,
	then it executes the responding functions */
int	ft_default_exec(char **argv, t_minishell *minishell_variable)
{
	char	*str;

	str = argv[0];
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(argv[1], minishell_variable));
	else if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd(minishell_variable));
	else if (ft_strcmp(str, "env") == 0)
		return (ft_env(minishell_variable));
	else if (ft_strcmp(str, "export") == 0)
		return (ft_export(argv, minishell_variable));
	else if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(argv, minishell_variable));
	ft_exit(argv, minishell_variable);
	return (ENO_GENERAL);
}

bool	found_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'' )
		delimiter++;
	return (!*delimiter);
}
