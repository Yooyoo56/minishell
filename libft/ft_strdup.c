/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:53:07 by whazami           #+#    #+#             */
/*   Updated: 2021/03/26 15:58:21 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		src_len;
	char	*strr;
	int		i;

	src_len = ft_strlen(s);
	strr = (char *)malloc(src_len + 1);
	if (strr == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		strr[i] = s[i];
		i++;
	}
	strr[i] = '\0';
	return (strr);
}
