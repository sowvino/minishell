/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:04:17 by selango           #+#    #+#             */
/*   Updated: 2024/06/05 16:23:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*final_list;

	final_list = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		if (!new_list)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&final_list, new_list);
		lst = lst->next;
	}
	return (final_list);
}
