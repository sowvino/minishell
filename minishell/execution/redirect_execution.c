/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-02 16:39:17 by selango           #+#    #+#             */
/*   Updated: 2025-01-02 16:39:17 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function helps to redirect the output as the input of
	another function handles both the > or >> functions in it.*/
int	ft_output_redirect(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_error_msg((t_error){ENO_GENERAL, ERR_UNCLEAR,
				io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_write_check(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

/*This function is to handle the input redirection .
It ensures that the input file is valid,opens it for reading*/
int	ft_input_redirect(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_error_msg((t_error){ENO_GENERAL, ERR_UNCLEAR,
				io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_RDONLY);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_read_check(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_append_redirect(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_error_msg((t_error){ENO_GENERAL, ERR_UNCLEAR,
				io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = ft_error_msg(ft_write_check(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
