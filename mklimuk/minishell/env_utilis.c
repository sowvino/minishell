/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-13 12:44:05 by selango           #+#    #+#             */
/*   Updated: 2024-11-13 12:44:05 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*deleting the ptr values*/
static void ft_del(void *ptr)
{
    free(ptr);
    ptr = NULL;
}
/*cleans the memory allocated in the strdup and substr function*/
void *ft_garbage_collector(void *ptr,bool clean)
{
    static t_list *garbage_list;
    if(clean)
    {
        ft_lstclear(&garbage_list,ft_del);
        return(NULL);
    }
    else
    {
        ft_lstadd_back(&garbage_list,ft_lstnew(ptr));
        return(ptr);
    }
}
// the function adding new element key-value to the end of envlist.
// if the list doesn't exist, it crates the new one
// or while current is not the last, it moves. and when we got the last element of the list it adds new elenet to the end.
void envlist_add_to_back(t_env *new)
{
	t_env *curr;
	curr = minishell_global.envlist;
	if (!curr)
	{
		minishell_global.envlist = new;
		return ;
	}
	while (curr -> next)
		curr = curr->next;
	curr->next = new;
}

// need to add a garbage collector!!!
// the function is adding or updating elements in envlist. 
// if flag is true, key and value will be added to the envlist because it means that they are not exist in the envlist.
// "while(envlist)"-loop and if(!ft_strcmp...)-condition : they are about changing key's value if we want to change it.
// if there is no such a key in the envlist and the flag is true, function will add key and value to the end of the list.
void envlist_updating (char *key, char *value, bool flag)
{
	t_env *envlist;

	envlist = minishell_global.envlist;
	while(envlist)
	{
		if (!ft_strcmp(key, envlist->key))
		{
			if (value)
				envlist->value = ft_garbage_collector(ft_strdup(value),false);
			return;
		}
		envlist = envlist->next;
	}
	if (flag)
		envlist_add_to_back(new_envlist(key, value));
}


