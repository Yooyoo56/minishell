/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:05:49 by ytak              #+#    #+#             */
/*   Updated: 2022/01/03 14:09:48 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	err_pipes(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `||'\n", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	err_pipe_space(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|' || line[i] == '\0')
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `|'\n", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	err_pipe_space_str(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
		ft_putstr_fd("unexpected token `|'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
