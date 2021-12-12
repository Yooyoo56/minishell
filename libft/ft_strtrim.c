/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:57:20 by whazami           #+#    #+#             */
/*   Updated: 2021/09/11 02:14:00 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	trim_start;
	size_t	trim_end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	trim_start = 0;
	while (ft_strchr(set, s1[i]) != NULL && s1[i++])
		trim_start++;
	i = ft_strlen(s1) - 1;
	trim_end = 0;
	while (ft_strrchr(set, s1[i--]) != NULL && trim_start != ft_strlen(s1))
		trim_end++;
	str = (char *)malloc(ft_strlen(s1) - trim_start - trim_end + 1);
	if (str == NULL)
		return (NULL);
	i = trim_start - 1;
	while (++i < ft_strlen(s1) - trim_end)
		str[i - trim_start] = s1[i];
	str[i - trim_start] = '\0';
	return (str);
}
