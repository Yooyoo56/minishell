/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_nl_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 07:21:30 by whazami           #+#    #+#             */
/*   Updated: 2021/12/13 07:21:49 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strchri(char *s, char c, int start, int stop)
{
	int	i;

	i = start;
	while (stop == -1 || i < stop)
	{
		if (s[i] == c)
			return (&s[i]);
		if (!s[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

void	erase_char(char *str, int index)
{
	int	i;

	i = index;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

char	get_non_printable(char c)
{
	if (c == ' ')
		return (ESPACE);
	if (c == '<')
		return (INF_);
	if (c == '>')
		return (SUP_);
	if (c == '|')
		return (PIPE_);
	return (c);
}
