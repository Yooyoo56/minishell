/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:02:56 by ytak              #+#    #+#             */
/*   Updated: 2021/12/17 22:09:43 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd_with_path(t_cmd *cmd, char **env)
{
	char	*path;
	char	*sub_path;
	char	*cmd_with_path;
	int		index[2];

	path = ft_getenv("PATH", env);
	cmd_with_path = ft_strdup(cmd->nom);
	index[0] = 0;
	while (cmd_with_path && access(cmd_with_path, F_OK) == -1)
	{
		index[1] = ft_strchri(path, ':', index[0], ft_strlen(path), 1) - path;
		sub_path = ft_substr(path, index[0], index[1] - index[0] + 1);
		sub_path[ft_strlen(sub_path) - 1] = '/';
		free(cmd_with_path);
		cmd_with_path = ft_strjoin(sub_path, cmd->nom);
		free(sub_path);
		index[0] = index[1] + 1;
		if (index[0] < 0)
		{
			free(cmd_with_path);
			cmd_with_path = NULL;
		}
	}
	free(path);
	return (cmd_with_path);
}

static void	non_built_in_command(t_cmd *cmd, char **env)
{
	char	*cmd_with_path;
	char	**args;
	int		pid;
	int		i;

	cmd_with_path = get_cmd_with_path(cmd, env);
	if (cmd_with_path == NULL)
		return ((void)printf("bash: %s: command not found\n", cmd->nom));
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
	pid = fork();
	if (pid == 0)
		execve(cmd_with_path, args, env);
	else
		waitpid(pid, NULL, 0);
	free(cmd_with_path);
	free_2d_array((void **)args);
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmd_name_is(cmds[i], "echo"))
			ft_echo(cmds[i]);
		else if (cmd_name_is(cmds[i], "env"))
			ft_env(*env);
		else if (cmd_name_is(cmds[i], "unset"))
			ft_unset(cmds[i], *env);
		else if (cmd_name_is(cmds[i], "export"))
			ft_export(cmds[i], env);
		else
			non_built_in_command(cmds[i], *env);
		i++;
	}
}
