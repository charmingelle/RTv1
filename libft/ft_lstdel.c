/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:41:04 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/03 13:02:26 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*buff;
	t_list	*lst;

	if (alst && del)
	{
		lst = *alst;
		while (lst)
		{
			del(lst->content, lst->content_size);
			buff = lst->next;
			ft_memdel((void **)&lst);
			lst = buff;
		}
		*alst = NULL;
	}
}
