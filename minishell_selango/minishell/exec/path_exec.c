/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-30 12:30:52 by selango           #+#    #+#             */
/*   Updated: 2024-12-30 12:30:52 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*this function has two parts it resolves and validates the executable paths*/

/* this function attempts  to find the executable cmd in directories
    it checks  and builds a executable path
    if executable path is found, it return the success and path
    if not found ,it returns the error msg*/
env_t_path ft_env_path(char *path,char *cmd)
{
    size_t  i;
    t_error error;
    char *command_path;
    char **split_path;

    i =0;
    if(!path || !cmd)
       return((env_t_path) {(t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,cmd},NULL}); 
    split_path = ft_split(path,:);
    if(!split_path)
        return((env_t_path) {(t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,cmd},NULL}); 
    while(split_path[i]!= '\0')
    {
        command_path = ft_strjoin_with_sep(ft_strdup(split_path[i]),ft_strdup(cmd),'/');
        command_path = ft_garbage_collector(joiner,false);
        error = ft_exec_check(command_path,true);
        if(error.no == ENO_SUCCESS)
        {
            ft_free_array(split_path);
            return((env_t_path){(t_error){ENO_SUCCESS,0,command_path},command_path});
        }  
        i++;    
    }
    ft_free_array(split_path);
    return((env_t_path) {(t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,cmd},NULL});
}
/*This function ft_get_exec_path is designed to find the path to a command (executable)*/

env_t_path ft_get_exec_path(char *cmd)
{
    char *value;

    if(!cmd)
        return((env_t_path) {(t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,cmd},NULL});
    if(ft_strnstr(cmd,"/",ft_strlen(cmd)))//checks whether if it a absolute or relative path in the cmd
        return((env_t_path){ft_exec_check(cmd,false),cmd});//it init the error msg (ft_exec_check) and cmd gives the path in env_t_path
    value = ft_search_envlist("PATH");
    if(value)   
        return(ft_env_path(value,cmd));
    return((env_t_path) {(t_error){ENO_NOT_FOUND,CMD_NOT_FOUND,cmd},NULL});
}

