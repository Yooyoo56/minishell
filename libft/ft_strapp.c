/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:26:20 by whazami           #+#    #+#             */
/*   Updated: 2021/12/24 06:40:44 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strapp(char **str, char *append)
{
	int	old_len;
	int	i;

	old_len = ft_strlen(*str);
	*str = ft_realloc(*str, old_len + 1,
			ft_strlen(*str) + ft_strlen(append) + 1);
	i = 0;
	while (i < (int)ft_strlen(append))
	{
		(*str)[old_len + i] = append[i];
		i++;
	}
	return (*str);
}
