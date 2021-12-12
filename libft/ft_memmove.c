/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:16:43 by whazami           #+#    #+#             */
/*   Updated: 2021/05/20 16:16:45 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cpy;
	const unsigned char	*src_cpy;
	int					i;

	dst_cpy = (unsigned char *)dst;
	src_cpy = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	i = 0;
	if (dst > src)
		while (len--)
			dst_cpy[len] = src_cpy[len];
	else
	{
		while (len--)
		{
			dst_cpy[i] = src_cpy[i];
			i++;
		}
	}
	return (dst);
}
