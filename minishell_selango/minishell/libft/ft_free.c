/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-30 14:15:41 by selango           #+#    #+#             */
/*   Updated: 2024-12-30 14:15:41 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_free_array(char **tofree)
{
    size_t i;

    if(!tofree)
        return;
    i = 0;
    while(tofree[i])
        free(tofree[i++]);
    free(tofree);
}

void    ft_free_array2(char ***tofree)
{
    size_t i;
    if(!tofree)
        return;
    i =0;
    while(tofree[i])
        ft_free_array(tofree[i++]);
    free(tofree);
}
