/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevrons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:03:16 by ytak              #+#    #+#             */
/*   Updated: 2021/12/29 14:55:05 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	err_multiple_chevrons(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
			{
				if (line[i + 2] == '<' || line[i + 2] == '>')
				{
					ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
					ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

int	err_chevrons_reverse(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<')
		{
			if (line[i + 1] == '>')
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
				return (1);
			}
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '<')
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
				return (1);
			}
		}
	}
	return (0);
}

int	err_chevrons_space(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '>' || line[i + 1] == '<')
				i++;
			i++;
			while (line[i] == ' ')
				i++;
			if (is_operator(line[i]) || line[i] == '\0')
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
