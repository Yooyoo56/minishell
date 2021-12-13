/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_new_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 05:45:38 by whazami           #+#    #+#             */
/*   Updated: 2021/12/13 05:45:42 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_start_end(char *line, int index[2], char *quote)
{
	int	i;

	i = index[1];
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			index[0] = i;
			*quote = line[i];
			break ;
		}
		i++;
	}
	i = index[0] + 1;
	while (line[i])
	{
		if (line[i] == *quote)
		{
			index[1] = i;
			break ;
		}
		i++;
	}
}

static void	manage_replacements(char *line, int index[2], char quote)
{
	int	i;

	if ((index[0] == 0 || ft_isspace(line[index[0] - 1])
			|| is_operator(line[index[0] - 1]))
		&& (ft_isspace(line[index[1] + 1]) || is_operator(line[index[1] + 1])
			|| line[index[1] + 1] == '\0') && index[1] == index[0] + 1)
	{
		erase_char(line, index[0]);
		index[1]--;
		line[index[0]] = END_;
		return ;
	}
	i = index[0] - 1;
	while (++i <= index[1])
	{
		if (line[i] == quote)
		{
			erase_char(line, i);
			index[1]--;
			i--;
		}
		else if (line[i] == ' ')
			line[i] = ESPACE;
		else if (line[i] == '<')
			line[i] = INF_;
		else if (line[i] == '>')
			line[i] = SUP_;
		else if (line[i] == '|')
			line[i] = PIPE_;
	}
}

static int	replace_env_var_by_val(char **line, char *var, int d_i, int *index)
{
	char	*var_expands;
	char	*tmps[3];
	int		sizes[2];

	var_expands = ft_strjoin("getenv(", var);
	tmps[0] = ft_strdup(var_expands);
	free(var_expands);
	var_expands = ft_strjoin(tmps[0], ")");
	free(tmps[0]);
	tmps[1] = ft_substr(*line, 0, d_i);
	tmps[2] = ft_substr(*line, d_i + ft_strlen(var) + 1, ft_strlen(*line));
	sizes[0] = ft_strlen(*line);
	tmps[0] = ft_strjoin(tmps[1], var_expands);
	free(*line);
	*line = ft_strjoin(tmps[0], tmps[2]);
	free(tmps[0]);
	sizes[1] = ft_strlen(*line);
	index[1] += sizes[1] - sizes[0];
	free(tmps[1]);
	free(tmps[2]);
	sizes[0] = ft_strlen(var_expands);
	free(var_expands);
	return (sizes[0]);
}

static void	manage_dollars(char **line, int index[2])
{
	char	*var_name;
	int		dollar_index;
	int		i;
	int		len_var_expands;

	dollar_index = index[0];
	len_var_expands = 0;
	while (ft_strchri(*line, '$', dollar_index + len_var_expands, index[1]))
	{
		dollar_index = ft_strchri(*line, '$',
				dollar_index + len_var_expands, index[1]) - *line;
		if (dollar_index < 0)
			break ;
		i = dollar_index;
		var_name = (char *)ft_calloc(index[1] - index[0] + 2, sizeof(char));
		while (++i < index[1] && (ft_isalnum((*line)[i]) || (*line)[i] == '_'))
			var_name[i - (dollar_index + 1)] = (*line)[i];
		len_var_expands = 1;
		if (ft_strlen(var_name))
			len_var_expands = replace_env_var_by_val
				(line, var_name, dollar_index, index);
		free(var_name);
	}
}

char	*generate_new_line(const char *line)
{
	char	*new_line;
	int		index[2];
	char	quote;

	new_line = ft_strdup(line);
	index[0] = 0;
	while (ft_strchri(new_line, '\'', index[0], -1))
	{
		index[1] = ft_strchri(new_line, '\'', index[0], -1) - new_line + 1;
		manage_dollars(&new_line, index);
		index[0] = ft_strchri(new_line, '\'', index[1], -1) - new_line + 1;
	}
	index[1] = ft_strlen(new_line);
	manage_dollars(&new_line, index);
	index[1] = 0;
	while (ft_strchri(new_line, '\'', index[1], -1)
		|| ft_strchri(new_line, '"', index[1], -1))
	{
		find_start_end(new_line, index, &quote);
		manage_replacements(new_line, index, quote);
		index[1]++;
	}
	return (new_line);
}
