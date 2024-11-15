/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-15 11:46:40 by selango           #+#    #+#             */
/*   Updated: 2024-11-15 11:46:40 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void skip_spaces(char *s,int *i,int *sign)
{
    while(s[*i] && s[*i] == ' ')
        (*i)++;
    if(s[*i] == '+' || s[*i] == '-')
    {
        if(s[*i] == -1)
            *sign *= -1;
        (*i)++;
    }  
}

static int atoi_exit(char *str)
{
    int i;
    int sign;
    unsigned long long result;
    int exit_str;

    i = 0;
    sign =1;
    result = 0;
    skip_spaces(str,&i,&sign);
    if(!ft_isdigit(str[i]))
    {
        exit_str = ft_error_msg((t_error){ERR_NUMERIC_REQUIRED,EN0_EXEC_ERROR,str});
        (ft_clean_ms(),exit(exit_str));
    }
    while(str[i])
    {
        result = (result *10) +(str[i] -'0');
        if(result > LONG_MAX)
        {
            exit_str = ft_error_msg((t_error){EN0_EXEC_ERROR ,EN0_EXEC_ERROR,str});
            (ft_clean_ms(),exit(exit_str));
        }
        i++;
    }
    return((result * sign) % 256);
}

void ft_exit(char **argv)
{
    int exit_str;
    exit_str = minishell_global.exit_str;
    if(argv[1])
    {
        if(argv[2] && ft_isdigit(argv[1]))
        {
            exit_str = ft_error_msg((t_error){ERR_TOO_MANY_ARGUMENTS,ENO_GENERAL,NULL});
            (ft_clean_ms(),exit(exit_str));
        }
        else
            exit_str = atoi_exit(argv[1]);
    }
    (ft_clean_ms(),exit(exit_str));
}
