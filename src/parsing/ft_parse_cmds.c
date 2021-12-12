/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:58 by whazami           #+#    #+#             */
/*   Updated: 2021/12/10 13:22:08 by whazami          ###   ########.fr       */
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
		|| is_operator(line[index[0] - 1])) && (ft_isspace(line[index[1] + 1])
		|| is_operator(line[index[1] + 1]) || line[index[1] + 1] == '\0')
		&& index[1] == index[0] + 1)
	{
		erase_char(line, index[0]);
		index[1]--;
		line[index[1]] = ' ';
		line[index[0]] = END_;
		return ;
	}
	i = index[0];
	while (i <= index[1])
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
		i++;
	}
}

static void	manage_env_variables(char **line, int index[2])
{
	char	*var_name;
	int 	dollar_index;
	int		i;
	char	*var_expands;
	char	*tmp;
	char	*tmp_line_start;
	char	*tmp_line_end;
	int		sizes[2];

	i = index[0];
	dollar_index = 0;
	var_expands = (char *)ft_calloc(1, sizeof(char));
	while (ft_strchri(*line, '$', index[0] + dollar_index + ft_strlen(var_expands)))
	{
		dollar_index = -1;
		while (i <= index[1])
		{
			if ((*line)[i] == '$')
			{
				dollar_index = i;
				break ;
			}
			i++;
		}
		if (dollar_index == -1)
			break ;
		i = dollar_index + 1;
		var_name = (char *)ft_calloc(index[1] - index[0] + 2, sizeof(char));
		while (i <= index[1] && (ft_isalpha((*line)[i]) || ft_isdigit((*line)[i]) 
				|| (*line)[i] == '_'))
		{
			var_name[i - (dollar_index + 1)] = (*line)[i];
			i++;
		}
		free(var_expands);
		if (!ft_strlen(var_name))
		{
			free(var_name);
			var_expands = (char *)ft_calloc(1, sizeof(char));
			dollar_index -= index[0];
			continue ;
		}
		var_expands = ft_strjoin("getenv(", var_name);
		tmp = ft_strdup(var_expands);
		free(var_expands);
		var_expands = ft_strjoin(tmp, ")");
		free(tmp);
		tmp_line_start = ft_substr(*line, 0, dollar_index);
		tmp_line_end = ft_substr(*line, dollar_index + ft_strlen(var_name) + 1, ft_strlen(*line));
		sizes[0] = ft_strlen(*line);
		*line = ft_strjoin(tmp_line_start, var_expands);
		tmp = ft_strdup(*line);
		free(*line);
		*line = ft_strjoin(tmp, tmp_line_end);
		free(tmp);
		sizes[1] = ft_strlen(*line);
		dollar_index -= index[0];
		index[1] += sizes[1] - sizes[0];
		free(var_name);
		free(tmp_line_start);
		free(tmp_line_end);
	}
	free(var_expands);
}

static void	modify_line(char **line)
{
	int		index[2];
	char	quote;

	index[0] = 0;
	while (ft_strchri(*line, '\'', index[0] + 1))
	{
		index[1] = ft_strchri(*line, '\'', index[0] + 1) - *line;
		manage_env_variables(line, index);
		index[0] = ft_strchri(*line, '\'', index[1] + 1) - *line;
	}
	index[1] = ft_strlen(*line) - 1;
	manage_env_variables(line, index);
	index[1] = 0;
	while (ft_strchri(*line, '\'', index[1]) || ft_strchri(*line, '"', index[1]))
	{
		find_start_end(*line, index, &quote);
		manage_replacements(*line, index, quote);
		index[1]++;
	}
}

static void	fill_redirs_and_remove_them(t_cmd* cmd, char *cmd_str)
{
	int		op_index;
	int		i;
	int		j;
	int		nb_spaces;
	t_op	op;

	cmd->redirs = (t_redir **)ft_calloc(1, sizeof(t_redir *));
	op = get_op(cmd_str, &op_index);
	i = 0;
	while (op != NONE)
	{
		cmd->redirs = (t_redir **)ft_realloc(cmd->redirs,
				(i + 1) * sizeof(t_redir *), (i + 2) * sizeof(t_redir *));
		cmd->redirs[i] = (t_redir *)ft_calloc(1, sizeof(t_redir));
		cmd->redirs[i]->op = op;
		cmd->redirs[i]->file = (char *)ft_calloc(1, sizeof(char));
		nb_spaces = 0;
		while (cmd_str[op_index + nb_spaces + 1] && ft_isspace(cmd_str[op_index + nb_spaces + 1]))
			nb_spaces++;
		j = 0;
		while (cmd_str[op_index + nb_spaces + j + 1] && !ft_isspace(cmd_str[op_index + nb_spaces + j + 1]))
		{
			cmd->redirs[i]->file = (char *)ft_realloc(cmd->redirs[i]->file,
											(j + 1) * sizeof(char), (j + 2) * sizeof(char));
			cmd->redirs[i]->file[j] = cmd_str[op_index + nb_spaces + j + 1];
			j++;
		}
		erase_chars_(cmd_str, op_index - (op == DOUBLE_INF || op == DOUBLE_SUP),
			1 + (op == DOUBLE_INF || op == DOUBLE_SUP) + nb_spaces + ft_strlen(cmd->redirs[i]->file));
		op = get_op(cmd_str, &op_index);
		i++;
	}
}

static void	fill_cmd(t_cmd *cmd, char *cmd_str)
{
	char		**words;
	int			is_minus;
	int			nb_args;
	int			j;

	words = ft_split(cmd_str, ' ');
	cmd->nom = ft_strdup(words[0]);
	is_minus = (words[0] && words[1] && words[1][0] == '-');
	cmd->flag = NULL;
	if (is_minus)
		cmd->flag = ft_strdup(words[1]);
	j = is_minus + 1;
	nb_args = 0;
	while (words[0] && words[nb_args + j])
		nb_args++;
	cmd->args = (char **)ft_calloc(nb_args + 1, sizeof(char *));
	cmd->args[0] = NULL;
	if (nb_args == 0)
		return ;
	j--;
	while (words[++j])
		cmd->args[j - (is_minus + 1)] = ft_strdup(words[j]);
	free_2d_array((void **)words);
}

void	parsing(char *line)
{
	t_cmd	**cmds;
	char	**cmds_strs;
	int		i;
	int		nb_cmds;

	// Yooyoo's part
	//if (parsing_error(line))
	//	return ;
	modify_line(&line);
	cmds_strs = ft_split(line, '|');
	nb_cmds = 0;
	while (cmds_strs[nb_cmds])
		nb_cmds++;
	cmds = (t_cmd **)ft_calloc(nb_cmds + 1, sizeof(t_cmd *));
	if (!cmds)
		return ;
	i = 0;
	while (i < nb_cmds)
	{
		cmds[i] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		fill_redirs_and_remove_them(cmds[i], cmds_strs[i]);
		i++;
	}
	i = 0;
	while (cmds_strs[i])
	{
		fill_cmd(cmds[i], cmds_strs[i]);
		i++;
	}
	i = 0;
	while (i < nb_cmds)
	{
		replace_non_printables(cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_cmds)
	{
		print_cmd(*cmds[i]);
		i++;
	}
	free_2d_array((void **)cmds_strs);
}
