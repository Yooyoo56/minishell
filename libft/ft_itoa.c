/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:25:03 by whazami           #+#    #+#             */
/*   Updated: 2021/06/03 14:25:06 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	long int	n_copy;
	char		*strr;

	len = ft_intlen(n);
	strr = (char *)malloc(len + 1);
	if (strr == NULL)
		return (NULL);
	strr[len--] = '\0';
	n_copy = (long int)n;
	if (n_copy == 0)
		strr[0] = '0';
	if (n_copy < 0)
	{
		strr[0] = '-';
		n_copy *= -1;
	}
	while (n_copy > 0)
	{
		strr[len--] = n_copy % 10 + '0';
		n_copy /= 10;
	}
	return (strr);
}
