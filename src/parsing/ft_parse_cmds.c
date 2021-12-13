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

static void	fill_redirs_and_remove_them(t_cmd *cmd, char *s)
{
	int		opi;
	int		i;
	int		j;
	int		nb_;
	int		d;

	cmd->redirs = (t_redir **)ft_calloc(1, sizeof(t_redir *));
	i = 0;
	while (get_op(s, &opi) != NONE)
	{
		write(1, "hey\n", 3);
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
				|| s[opi + nb_ + j] == '_' || s[opi + nb_ + j] == '.'))
			cmd->redirs[i]->file[j - 1] = s[opi + nb_ + j];
		d = (get_op(s, &opi) == DOUBLE_INF || get_op(s, &opi) == DOUBLE_SUP);
		erase_str(s, opi - d, 1 + d + nb_ + ft_strlen(cmd->redirs[i++]->file));
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
		return (free_2d_array((void **)words));
	j--;
	while (words[++j])
		cmd->args[j - (is_minus + 1)] = ft_strdup(words[j]);
	free_2d_array((void **)words);
}

t_cmd	**parsing(const char *line)
{
	t_cmd	**cmds;
	char	**cmds_strs;
	char	*new_line;
	int		i;

	// Yooyoo's part
	//if (parsing_error(line))
	//	return ;
	new_line = generate_new_line(line);
	cmds_strs = ft_split(new_line, '|');
	printf("new_line: %p\n", new_line);
	printf("strs: %p\n", cmds_strs);
	printf("cmds_strs 0: %p\n", cmds_strs[0]);
	printf("cmds_strs 1: %p\n", cmds_strs[1]);
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
