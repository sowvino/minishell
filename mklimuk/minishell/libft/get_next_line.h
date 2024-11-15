/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-01 16:48:07 by selango           #+#    #+#             */
/*   Updated: 2024-07-01 16:48:07 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
        
char    *get_next_line(int fd);
size_t  ft_strlen(const char *str);
char    *ft_strdup(const char *src);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strchr(const char *s, int c);



#endif