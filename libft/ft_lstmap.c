/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:54:48 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/01 19:48:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_result(t_list *result)
{
	t_list *temp;

	while (result)
	{
		free(result->content);
		temp = result;
		result = result->next;
		free(temp);
	}
}

static void	push_back(t_list **list, t_list *new)
{
	if (!list)
		return ;
	while (*list)
		list = &(*list)->next;
	*list = new;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*result;

	new = 0;
	result = 0;
	if (f)
		while (lst)
		{
			new = f(ft_lstnew(lst->content, lst->content_size));
			if (!new)
			{
				if (result)
					free_result(result);
				return (0);
			}
			push_back(&result, new);
			new = new->next;
			lst = lst->next;
		}
	return (result);
}
