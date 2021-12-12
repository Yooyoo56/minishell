/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:22:19 by whazami           #+#    #+#             */
/*   Updated: 2021/06/08 16:22:20 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstr;
	t_list	*begin_lstr;
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	lstr = ft_lstnew(f(lst->content));
	if (!lstr)
		return (NULL);
	begin_lstr = lstr;
	lst = lst->next;
	while (lst)
	{
		new_lst = ft_lstnew(f(lst->content));
		if (!new_lst)
		{
			ft_lstclear(&begin_lstr, del);
			return (NULL);
		}
		lstr->next = new_lst;
		lstr = lstr->next;
		lst = lst->next;
	}
	return (begin_lstr);
}
