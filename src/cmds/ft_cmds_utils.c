/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:10:42 by whazami           #+#    #+#             */
/*   Updated: 2021/12/17 22:26:59 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd_with_path(t_cmd *cmd, char **env)
{
	char		*path;
	char		*sub_path;
	char		*cmd_with_path;
	long int	index[2];

	path = ft_getenv("PATH", env);
	cmd_with_path = ft_strdup(cmd->nom);
	index[0] = 0;
	while (index[0] >= 0 && access(cmd_with_path, F_OK) == -1)
	{
		index[1] = ft_strchri(path, ':', index[0], ft_strlen(path)) - path;
		sub_path = ft_substr(path, index[0], index[1] - index[0]);
		ft_strapp(&sub_path, "/");
		free(cmd_with_path);
		cmd_with_path = ft_strjoin(sub_path, cmd->nom);
		free(sub_path);
		index[0] = index[1] + 1;
	}
	if (access(cmd_with_path, F_OK) == -1)
	{
		free(cmd_with_path);
		cmd_with_path = NULL;
	}
	free(path);
	return (cmd_with_path);
}

void	non_built_in_command(t_cmd *cmd, char **env)
{
	char	*cmd_with_path;
	char	**args;
	int		i;

	cmd_with_path = get_cmd_with_path(cmd, env);
	if (cmd_with_path == NULL)
	{
		print_err(cmd->nom, "command not found", NULL);
		if (cmd->exit == 0)
			cmd->exit = 127;
		return ;
	}
	args = ft_calloc(2, sizeof(char *));
	args[0] = ft_strdup(cmd->nom);
	i = 0;
	while (cmd->args[i])
	{
		args = ft_realloc(args, (i + 2) * sizeof(char *),
				(i + 3) * sizeof(char *));
		args[i + 1] = ft_strdup(cmd->args[i]);
		i++;
	}
	execve(cmd_with_path, args, env);
}

int	cmd_name_is(t_cmd *cmd, char *str)
{
	if (cmd->nom)
		return (ft_strcmp(cmd->nom, str) == 0);
	return (0);
}

int	is_built_in_cmd(t_cmd *cmd)
{
	if (cmd->nom)
		return (cmd_name_is(cmd, "echo") || cmd_name_is(cmd, "env")
			|| cmd_name_is(cmd, "unset") || cmd_name_is(cmd, "export")
			|| cmd_name_is(cmd, "cd") || cmd_name_is(cmd, "pwd")
			|| cmd_name_is(cmd, "exit"));
	return (1);
}
