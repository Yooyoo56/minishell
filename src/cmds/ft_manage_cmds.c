/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:02:56 by ytak              #+#    #+#             */
/*   Updated: 2022/01/04 13:45:46 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

/* if create == 1 then create the pipes
 * else close them */
static void	manage_pipes(int (**pipes)[2], t_cmd **cmds, int create)
{
	int	i;

	if (create == 1)
	{
		manage_heredocs(cmds);
		*pipes = NULL;
	}
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

/* if save == 1 then save stdout and stdin in std_fds
 * else cancel all previous redirections and close std_fds */
static void	manage_std_fds(int std_fds[2], int pid, int save)
{
	if (pid == -1)
	{
		if (save)
		{
			std_fds[0] = dup(STDIN_FILENO);
			std_fds[1] = dup(STDOUT_FILENO);
		}
		else
		{
			dup2(std_fds[0], STDIN_FILENO);
			dup2(std_fds[1], STDOUT_FILENO);
			close(std_fds[0]);
			close(std_fds[1]);
		}
	}
}

static void	exec_cmd_by_name(t_cmd *cmd, char ***env)
{
	if (cmd_name_is(cmd, "env"))
		ft_env(*env);
	else if (cmd_name_is(cmd, "unset"))
		ft_unset(cmd, *env);
	else if (cmd_name_is(cmd, "export"))
		ft_export(cmd, env);
	else if (cmd_name_is(cmd, "echo"))
		ft_echo(cmd);
	else if (cmd_name_is(cmd, "pwd"))
		ft_pwd();
	else if (cmd_name_is(cmd, "cd"))
		ft_cd(cmd, *env);
	else if (cmd_name_is(cmd, "exit"))
		ft_exit(cmd);
	else if (cmd->nom)
		non_built_in_command(cmd, *env);
	if (cmd->pid == 0)
		exit(cmd->exit);
}

static void	wait_children(t_cmd **cmds)
{
	int	i;
	int	status;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
			waitpid(cmds[i]->pid, NULL, 0);
		else
		{
			waitpid(cmds[i]->pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				return ;
			}
		}
		i++;
	}
	g_exit_code = cmds[0]->exit;
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	(*pipes)[2];
	int	std_fds[2];
	int	i;

	manage_pipes(&pipes, cmds, 1);
	i = -1;
	while (cmds[++i])
	{
		if (!is_built_in_cmd(cmds[i]) || i > 0 || cmds[i + 1])
			cmds[i]->pid = fork();
		if (cmds[i]->pid == 0 || cmds[i]->pid == -1)
		{
			if (cmds[i + 1])
				dup2(pipes[i][1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			manage_pipes(&pipes, cmds, 0);
			manage_std_fds(std_fds, cmds[i]->pid, 1);
			if (manage_redirs(cmds[i]))
				exec_cmd_by_name(cmds[i], env);
			manage_std_fds(std_fds, cmds[i]->pid, 0);
		}
	}
	manage_pipes(&pipes, cmds, 0);
	wait_children(cmds);
}
