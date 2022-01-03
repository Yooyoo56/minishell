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

static void	exec_cmd_by_name(t_cmd *cmd, char ***env)
{
	if (cmd_name_is(cmd, "echo"))
		ft_echo(cmd);
	else if (cmd_name_is(cmd, "env"))
		ft_env(*env);
	else if (cmd_name_is(cmd, "unset"))
		ft_unset(cmd, *env);
	else if (cmd_name_is(cmd, "export"))
		ft_export(cmd, env);
	else if (cmd->nom)
		non_built_in_command(cmd, *env);
	if (cmd->pid == 0)
		exit(cmd->exit);
}

/* if save == 1 then save stdout and stdin in std_fds
 * else cancel all previous redirections and close std_fds */
static void manage_std_fds(int std_fds[2], int pid, int save)
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

static int	manage_redirs(t_cmd *cmd)
{
	int			fd_in;
	int			fd_out;
	int			i;
	
	i = 0;
	while (cmd->redirs[i])
	{
		if (cmd->redirs[i]->op == OUT)
			fd_out = open(cmd->redirs[i]->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (cmd->redirs[i]->op == APPEND)
			fd_out = open(cmd->redirs[i]->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (cmd->redirs[i]->op == IN)
		{
			fd_in = open(cmd->redirs[i]->file, O_RDONLY);
			if (fd_in == -1)
			{
				print_err(cmd->redirs[i]->file, "No such file or directory", 0);
				if (cmd->pid == 0)
					exit(1);
				return (0);
			}
		}
		if (cmd->redirs[i]->op == OUT || cmd->redirs[i]->op == APPEND)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (cmd->redirs[i]->op == IN || cmd->redirs[i]->op == HEREDOC)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		i++;
	}
	return (1);
}

static void	wait_children(t_cmd **cmds)
{
	int i;
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
				exit_code = WEXITSTATUS(status);
				return ;
			}
		}
		i++;
	}
	exit_code = cmds[0]->exit;
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	(*pipes)[2];
	int	std_fds[2];
	int	i;

	manage_pipes(&pipes, (const t_cmd **)cmds, 1);
	i = 0;
	while (cmds[i])
	{
		if (!is_built_in_cmd(cmds[i]) || i > 0 || cmds[i + 1])
			cmds[i]->pid = fork();
		if (cmds[i]->pid == 0 || cmds[i]->pid == -1)
		{
			if (cmds[i + 1])
				dup2(pipes[i][1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			manage_pipes(&pipes, (const t_cmd **)cmds, 0);
			manage_std_fds(std_fds, cmds[i]->pid, 1);
			if (manage_redirs(cmds[i]))
				exec_cmd_by_name(cmds[i], env);
			manage_std_fds(std_fds, cmds[i]->pid, 0);
		}
		i++;
	}
	manage_pipes(&pipes, (const t_cmd **)cmds, 0);
	wait_children(cmds);
}
