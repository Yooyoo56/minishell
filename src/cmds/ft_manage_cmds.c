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

static void	non_built_in_command(t_cmd *cmd, char **env)
{
	char	*cmd_with_path;
	char	**args;
	int		i;

	cmd_with_path = get_cmd_with_path(cmd, env);
	if (cmd_with_path == NULL)
	{
		printf("bash: %s: command not found\n", cmd->nom);
		if (cmd->exit == 0)
			cmd->exit = 127;
		exit(cmd->exit);
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

static void	get_env_from_child(t_cmd *cmd, char ***env, int fd[2])
{
	char	*env_line;
	int		i;

	i = -1 * (cmd->pid == 0);
	if (cmd->pid != 0)
	{
		free_2d_array((void **)*env);
		*env = ft_calloc(1, sizeof(char *));
		while (get_next_line(fd[0], &env_line) && !ft_strchr(env_line, '\04'))
		{
			*env = ft_realloc(*env, (i + 1) * sizeof(char *),
					(i + 2) * sizeof(char *));
			(*env)[i++] = ft_strdup(env_line);
			free(env_line);
		}
		free(env_line);
	}
	else
	{
		while ((*env)[++i])
			ft_putstr_fd(ft_strapp(&(*env)[i], "\n"), fd[1]);
		free_2d_array((void **)*env);
		ft_putstr_fd("\04\n", fd[1]);
		exit(cmd->exit);
	}
}

static void	exec_cmd_by_name(t_cmd *cmd, char ***env)
{
	int	fd_env[2];

	pipe(fd_env);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd_name_is(cmd, "echo"))
			ft_echo(cmd);
		else if (cmd_name_is(cmd, "env"))
			ft_env(*env, cmd->exit);
		else if (cmd_name_is(cmd, "unset"))
			ft_unset(cmd, *env);
		else if (cmd_name_is(cmd, "export"))
			ft_export(cmd, env);
		else
			non_built_in_command(cmd, *env);
	}
	if (cmd_name_is(cmd, "export") || cmd_name_is(cmd, "unset"))
		get_env_from_child(cmd, env, fd_env);
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		exec_cmd_by_name(cmds[i], env);
		i++;
	}
	i = 0;
	while (cmds[i])
	{
		waitpid(cmds[i]->pid, NULL, 0);
		i++;
	}
}
