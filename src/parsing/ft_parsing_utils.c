/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:32:29 by whazami           #+#    #+#             */
/*   Updated: 2021/12/13 17:04:34 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	erase_str(char *str, int start, int nb_chars)
{
	int	i;

	i = start;
	while (str[i + nb_chars])
	{
		str[i] = str[i + nb_chars];
		i++;
	}
	str[i] = '\0';
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_op	get_op(char *line, int *op_index)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
			{
				*op_index = i + 1;
				if (line[i] == '<')
					return (DOUBLE_INF);
				return (DOUBLE_SUP);
			}
			*op_index = i;
			if (line[i] == '<')
				return (INF);
			return (SUP);
		}
		i++;
	}
	return (NONE);
}
