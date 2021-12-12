/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:25:47 by whazami           #+#    #+#             */
/*   Updated: 2021/03/18 15:58:00 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	len_src;
	unsigned int	len_dest;
	unsigned int	cpt;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (!size)
		return (len_src);
	if (size <= len_dest)
		return (size + len_src);
	cpt = 0;
	while (cpt < size - len_dest - 1 && src[cpt] != '\0')
	{
		dest[cpt + len_dest] = src[cpt];
		cpt++;
	}
	dest[cpt + len_dest] = '\0';
	return (len_src + len_dest);
}
