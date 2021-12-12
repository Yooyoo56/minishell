/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:50:47 by whazami           #+#    #+#             */
/*   Updated: 2021/06/03 13:50:52 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*strr;
	int		i;

	if (!s || !f)
		return (NULL);
	strr = (char *)malloc(ft_strlen(s) + 1);
	if (!strr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		strr[i] = f(i, s[i]);
		i++;
	}
	strr[i] = '\0';
	return (strr);
}
