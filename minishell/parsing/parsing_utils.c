/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:53 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:53 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	priority(void)
{
	return (1);
}

void	free_2d_array(char **two_d_array)
{
	size_t	i;

	if (!two_d_array)
		return ;
	i = 0;
	while (two_d_array[i])
		free(two_d_array[i++]);
	free(two_d_array);
}

void	free_3d_array(char ***three_d_array)
{
	size_t	i;

	i = 0;
	if (!three_d_array)
		return ;
	while (three_d_array[i])
		free_2d_array(three_d_array[i++]);
	free(three_d_array);
}
