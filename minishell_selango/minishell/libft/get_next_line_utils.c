/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-01 16:47:41 by selango           #+#    #+#             */
/*   Updated: 2024-07-01 16:47:41 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char *ft_strdup(const char *src)
{
    char *new;
    int len;

    len = 0;
    while (src[len] != '\0')
        len++;
    new = (char *)malloc((len + 1) * sizeof(char));
    if (!new)
        return (0);
    while (len >= 0)
    {
        new[len] = src[len];
        len--;
    }
    return (new);
}

int ft_totlen(char *s1, char *s2)
{
    int len1;
    int len2;
    int totlen;

    len1 = ft_strlen((char *)s1);
    len2 = ft_strlen((char *)s2);
    totlen = len1 + len2;
    return (totlen);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    int totlen;
    char *newstr;
    int i;
    int j;

    totlen = ft_totlen((char *)s1, (char *)s2);
    newstr = (char *)malloc((totlen + 1) * sizeof(char));
    if (newstr == NULL)
        return (NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        newstr[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
    {
        newstr[i + j] = s2[j];
        j++;
    }
    newstr[i + j] = '\0';
    return (newstr);
}

char *ft_strchr(const char *s, int c)
{
    char a;
    int i;

    a = (char)c;
    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == a)
        {
            return ((char *)&s[i]);
        }
        i++;
    }
    if (a == '\0')
    {
        return ((char *)&s[i]);
    }
    return (NULL);
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    char *substr;
    size_t i;
    size_t strlength;

    i = 0;
    if (s == NULL)
        return (NULL);
    strlength = ft_strlen((char *)s);
    if (start >= strlength)
        return (ft_strdup(""));
    if (start + len > strlength)
        len = strlength - start;
    substr = malloc((len + 1) * sizeof(char));
    if (substr == NULL)
        return (NULL);
    while (i < len && s[start + i] != '\0')
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return (substr);
}
