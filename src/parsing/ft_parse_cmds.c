/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:58 by whazami           #+#    #+#             */
/*   Updated: 2022/01/12 13:02:36 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_redirs_and_remove_them(t_cmd *cmd, char *s)
{
	int		opi;
	int		i;
	int		j;
	int		nb_;

	cmd->redirs = (t_redir **)ft_calloc(1, sizeof(t_redir *));
	i = 0;
	while (get_op(s, &opi) != NONE)
	{
		cmd->redirs = (t_redir **)ft_realloc(cmd->redirs,
				(i + 1) * sizeof(t_redir *), (i + 2) * sizeof(t_redir *));
		cmd->redirs[i] = (t_redir *)ft_calloc(1, sizeof(t_redir));
		cmd->redirs[i]->op = get_op(s, &opi);
		nb_ = 0;
		while (s[opi + nb_ + 1] && ft_isspace(s[opi + nb_ + 1]))
			nb_++;
		j = 0;
		cmd->redirs[i]->file = (char *)ft_calloc(ft_strlen(s), sizeof(char));
		while (s[opi + nb_ + ++j] && (ft_isalnum(s[opi + nb_ + j])
				|| s[opi + nb_ + j] == '_' || s[opi + nb_ + j] == '-'
				|| s[opi + nb_ + j] == '.' || s[opi + nb_ + j] == '/'))
			cmd->redirs[i]->file[j - 1] = s[opi + nb_ + j];
		j = (get_op(s, &opi) == HEREDOC || get_op(s, &opi) == APPEND);
		erase_str(s, opi - j, 1 + j + nb_ + ft_strlen(cmd->redirs[i++]->file));
	}
}

static void	fill_cmd(t_cmd *cmd, char *cmd_str)
{
	char		**words;
	int			nb_args;
	int			j;

	words = ft_split(cmd_str, ' ');
	cmd->nom = ft_strdup(words[0]);
	cmd->pid = -1;
	cmd->exit = 0;
	j = 1;
	nb_args = 0;
	while (words[0] && words[nb_args + j])
		nb_args++;
	cmd->args = (char **)ft_calloc(nb_args + 1, sizeof(char *));
	cmd->args[0] = NULL;
	if (nb_args == 0)
		return (free_2d_array((void **)words));
	j--;
	while (words[++j])
		cmd->args[j - 1] = ft_strdup(words[j]);
	free_2d_array((void **)words);
}

static void	replace_non_printables_in_str(char *str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == ESPACE)
				str[i] = ' ';
			else if (str[i] == INF)
				str[i] = '<';
			else if (str[i] == SUP)
				str[i] = '>';
			else if (str[i] == PIPE)
				str[i] = '|';
			else if (str[i] == END_)
				str[i] = '\0';
			i++;
		}
	}
}

static void	replace_non_printables(t_cmd *cmd)
{
	int	i;

	replace_non_printables_in_str(cmd->nom);
	i = 0;
	while (cmd->args[i])
	{
		replace_non_printables_in_str(cmd->args[i]);
		i++;
	}
}

t_cmd	**parsing(const char *line, char **env)
{
	t_cmd	**cmds;
	char	**cmds_strs;
	char	*new_line;
	int		i;

	if (parsing_error(line))
		return (NULL);
	new_line = generate_new_line(line, env);
	g_exit_code = 0;
	cmds_strs = ft_split(new_line, '|');
	free(new_line);
	cmds = NULL;
	i = -1;
	while (cmds_strs[++i])
	{
		cmds = ft_realloc(cmds, (i + 1) * sizeof(t_cmd *),
				(i + 2) * sizeof(t_cmd *));
		cmds[i] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		fill_redirs_and_remove_them(cmds[i], cmds_strs[i]);
		fill_cmd(cmds[i], cmds_strs[i]);
		replace_non_printables(cmds[i]);
	}
	free_2d_array((void **)cmds_strs);
	return (cmds);
}
