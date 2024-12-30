/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-30 13:00:44 by selango           #+#    #+#             */
/*   Updated: 2024-12-30 13:00:44 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_totlen(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	totlen;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	totlen = len1 + len2;
	return (totlen);
}

char *ft_strjoin_with_sep(char *s1,char *s2,char c)
{
    int totlen;
    char *newstr;
    int i;
    int j;

    if (!s1 || !s2)
    return (NULL);
    if (!c || !ft_strlen(s1) || !ft_strlen(s2))
        return (ft_strjoin(s1, s2));
    totlen = ft_totlen(s1,s2) + 1;
    newstr = malloc((totlen +1) * sizeof(char));
    if(!newstr)
        return(NULL);
    i =0;
    while(s1[i] != '\0')
    {
        newstr[i] = s1[i];
        i++;
    }
    newstr[i++] = c;
    j =0;
    while(s2[j] != '\0')
        newstr[i + j] = s2[j++];
    newstr[i + j] = '\0';
    return(newstr);
}
