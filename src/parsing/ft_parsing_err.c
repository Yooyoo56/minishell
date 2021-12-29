/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:46:18 by ytak              #+#    #+#             */
/*   Updated: 2021/12/29 16:00:11 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_combine_quotes(const char *line)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote = line[i];
			i++;
			if (line[i] == '\0')
				return (printf("bash: syntax error `\'' `\"' \n") > 0);
			while (line[i])
			{
				if (line[i] == quote)
					break ;
				if (line[i + 1] == '\0')
					return (printf("bash: syntax error `\'' `\"' \n") > 0);
				i++;
			}
		}
		if (line[i])
			i++;
	}
	return (0);
}

int	err_slash(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			printf("bash: syntax error near unexpected token `\\' \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	err_semicolon(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
		{
			printf("bash: syntax error near unexpected token `;' \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing_error(const char *line)
{
	if (ft_strlen(line) > 1000000000)
	{
		printf("Error! Malloc error! Line too long\n");
		return (1);
	}
	if (err_multiple_chevrons(line))
		return (1);
	if (err_chevrons_reverse(line))
		return (1);
	if (err_pipes(line))
		return (1);
	if (err_slash(line))
		return (1);
	if (err_semicolon(line))
		return (1);
	if (err_chevrons_space(line))
		return (1);
	if (err_pipe_space(line))
		return (1);
	if (err_pipe_space_str(line))
		return (1);
	if (err_combine_quotes(line))
		return (1);
	return (0);
}
