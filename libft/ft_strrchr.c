/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:44:18 by whazami           #+#    #+#             */
/*   Updated: 2021/05/21 22:44:21 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*begin;

	begin = s;
	s += ft_strlen(s);
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (s == begin)
			return (NULL);
		s--;
	}
}
