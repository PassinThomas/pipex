/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:58:22 by tpassin           #+#    #+#             */
/*   Updated: 2024/02/26 05:24:03 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst && lst != NULL)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			while (list)
			{
				tmp = list->next;
				(*del)(list->content);
				free(list);
				list = tmp;
			}
			lst = NULL;
		}
		ft_lstadd_back(&list, tmp);
		lst = lst->next;
	}
	return (list);
}
