/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:58:17 by whazami           #+#    #+#             */
/*   Updated: 2021/06/07 18:58:19 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	p = *alst;
	while (p->next)
		p = p->next;
	p->next = new;
}
