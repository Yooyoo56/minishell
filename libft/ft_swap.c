/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:19:06 by whazami           #+#    #+#             */
/*   Updated: 2021/12/16 21:28:58 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t len)
{
	unsigned char	*p;
	unsigned char	*q;
	unsigned char	tmp;
	size_t			i;

	p = a;
	q = b;
	i = 0;
	while (i < len)
	{
		tmp = p[i];
		p[i] = q[i];
		q[i] = tmp;
		i++;
	}
}
