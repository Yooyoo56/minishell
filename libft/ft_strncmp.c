/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:07:44 by whazami           #+#    #+#             */
/*   Updated: 2021/03/21 13:45:53 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	cpt;

	cpt = 0;
	if (n == 0)
		return (0);
	while (s1[cpt] && s2[cpt] && s1[cpt] == s2[cpt] && cpt < n - 1)
		cpt++;
	return ((unsigned char)s1[cpt] - (unsigned char)s2[cpt]);
}
