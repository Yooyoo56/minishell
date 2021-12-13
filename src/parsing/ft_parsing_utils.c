/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:32:29 by whazami           #+#    #+#             */
/*   Updated: 2021/12/10 13:32:32 by whazami          ###   ########.fr       */
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

void	replace_non_printables_in_str(char *str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == ESPACE)
				str[i] = ' ';
			else if (str[i] == INF_)
				str[i] = '<';
			else if (str[i] == SUP_)
				str[i] = '>';
			else if (str[i] == PIPE_)
				str[i] = '|';
			else if (str[i] == END_)
				str[i] = '\0';
			i++;
		}
	}
}

void	replace_non_printables(t_cmd *cmd)
{
	int	i;

	replace_non_printables_in_str(cmd->nom);
	replace_non_printables_in_str(cmd->flag);
	i = 0;
	while (cmd->args[i])
	{
		replace_non_printables_in_str(cmd->args[i]);
		i++;
	}
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
