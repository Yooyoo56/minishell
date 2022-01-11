/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:46:18 by ytak              #+#    #+#             */
/*   Updated: 2021/12/29 16:53:29 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	print_quote_err(void)
{
	ft_putstr_fd("bash: syntax error `\'' `\"' \n", STDERR_FILENO);
	return (1);
}

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
				return (print_quote_err());
			while (line[i])
			{
				if (line[i] == quote)
					break ;
				if (line[i + 1] == '\0')
					return (print_quote_err());
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
			ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
			ft_putstr_fd("unexpected token `\\'\n", STDERR_FILENO);
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
			ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
			ft_putstr_fd("unexpected token `;'\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing_error(const char *line)
{
	if (err_multiple_chevrons(line) || err_chevrons_reverse(line)
		|| err_chevrons_space(line) || err_slash(line) || err_semicolon(line)
		|| err_pipe_space_str(line) || err_pipes(line) || err_pipe_space(line)
		|| err_combine_quotes(line))
	{
		g_exit_code = 258;
		return (1);
	}
	return (0);
}
