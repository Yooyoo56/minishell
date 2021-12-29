/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:05:49 by ytak              #+#    #+#             */
/*   Updated: 2021/12/29 16:01:03 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				printf("bash: syntax error near unexpected token `||'\n");
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
				printf("bash: syntax error near unexpected token `|'\n");
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
	while (line[i])
	{
		if (line[i] == '|')
		{
//			if (line[i + 1] == '|')
//				i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|'  || line[i] == '\0')
			{
				printf("Yooyoo did it when wael is in USA. So, there are some problems..\n");
//				printf("bash: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
