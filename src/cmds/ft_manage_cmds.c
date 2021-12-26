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

/* if create == 1 then create the pipes
 * else close them */
static void	manage_pipes(int (**pipes)[2], const t_cmd **cmds, int create)
{
	int	i;

	if (create == 1)
		*pipes = NULL;
	i = 0;
	while (cmds[i + 1])
	{
		if (create)
		{
			*pipes = ft_realloc(*pipes, i * sizeof(int *),
					(i + 1) * sizeof(int *));
			pipe((*pipes)[i]);
		}
		else
		{
			close((*pipes)[i][0]);
			close((*pipes)[i][1]);
		}
		i++;
	}
	if (create == 0)
		free(*pipes);
}

static void	exec_cmd_by_name(t_cmd *cmd, char ***env, int fd_env[2], int getenv)
{
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
	if ((cmd_name_is(cmd, "export") || cmd_name_is(cmd, "unset")) && getenv)
		get_env_from_child(cmd, env, fd_env);
	if (cmd->pid == 0)
		exit(cmd->exit);
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	(*pipes)[2];
	int	fd_env[2];
	int	i;

	manage_pipes(&pipes, (const t_cmd **)cmds, 1);
	pipe(fd_env);
	i = 0;
	while (cmds[i])
	{
		cmds[i]->pid = fork();
		if (cmds[i]->pid == 0)
		{
			if (cmds[i + 1])
				dup2(pipes[i][1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			manage_pipes(&pipes, (const t_cmd **)cmds, 0);
		}
		exec_cmd_by_name(cmds[i], env, fd_env, (i == 0 && cmds[i + 1] == NULL));
		i++;
	}
	manage_pipes(&pipes, (const t_cmd **)cmds, 0);
	i = 0;
	while (cmds[i])
		waitpid(cmds[i++]->pid, NULL, 0);
}
