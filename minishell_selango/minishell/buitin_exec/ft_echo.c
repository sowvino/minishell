/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 10:57:34 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 10:57:34 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*To implement the behavior of the -n in echo function. This fn checks whether - or n is found in the str and return 1 if it is found else it return 0*/
static int operator_checker(char *str)
{
    int i;
    i =0;
    if(str[i] != '-')
        return(0);
    while(str[i])
    {
        if(str[i] != 'n')
            return(0);
        i++;
    }
    return(1);
}
/*this fn replicate the echo cmd on the terminal.checks for the operator if yes then it does not print the newline*/
int ft_echo(char **argv)
{
    int i;
    int operator;
    
    i =1;//checks after the echo cmd from the commandline
    operator = 0;
    while(argv[i] && operator_checker(argv[i]) == 1)
    {
        operator = 1;
        i++;
    }
    while(argv[i])
    {
        ft_putstr_fd(argv[i],1);
        if(argv[i +1])
            ft_putstr_fd(" ",1);
        i++;
    }
    if(operator == 0)
        ft_putstr_fd("\n",1);
    return(0);
}
