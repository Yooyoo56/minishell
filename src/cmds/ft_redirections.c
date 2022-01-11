/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 06:57:31 by whazami           #+#    #+#             */
/*   Updated: 2022/01/10 19:57:36 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	user_write_in_hdoc_file(int hdoc_fd, char *eof)
{
	char	*line;

	line = readline("> ");
	if (line != NULL)
	{
		while (ft_strcmp(line, eof) != 0)
		{
			write(hdoc_fd, line, ft_strlen(line));
			write(hdoc_fd, "\n", 1);
			free(line);
			line = readline("> ");
			if (line == NULL)
				break ;
		}
	}
	free(line);
	close(hdoc_fd);
}

static int	create_hdoc_file(char **redir_file)
{
	char	*hdoc_file;
	int		fd;
	int		k;
	char	*k_str;

	hdoc_file = ft_strdup("/tmp/.hdoc_0");
	k = 1;
	while (access(hdoc_file, F_OK) == 0)
	{
		k_str = ft_itoa(k);
		free(hdoc_file);
		hdoc_file = ft_strjoin("/tmp/.hdoc_", k_str);
		free(k_str);
		k++;
	}
	fd = open(hdoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	free(*redir_file);
	*redir_file = ft_strdup(hdoc_file);
	free(hdoc_file);
	return (fd);
}

void	manage_heredocs(t_cmd **cmds)
{
	int		i;
	int		j;
	char	*eof;
	int		fd;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->redirs[j])
		{
			if (cmds[i]->redirs[j]->op == HEREDOC)
			{
				eof = ft_strdup(cmds[i]->redirs[j]->file);
				fd = create_hdoc_file(&cmds[i]->redirs[j]->file);
				user_write_in_hdoc_file(fd, eof);
				free(eof);
			}
			j++;
		}
		i++;
	}
}

static int	init_fd(int *fd_in, int *fd_out, t_redir *redir, t_cmd *cmd)
{
	if (redir->op == OUT)
		*fd_out = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (redir->op == APPEND)
		*fd_out = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (redir->op == IN || redir->op == HEREDOC)
	{
		*fd_in = open(redir->file, O_RDONLY);
		if (*fd_in == -1)
		{
			print_err(redir->file, "No such file or directory", 0);
			if (cmd->pid == 0)
				exit(1);
			cmd->exit = 1;
			return (0);
		}
	}
	return (1);
}

int	manage_redirs(t_cmd *cmd)
{
	int			fd_in;
	int			fd_out;
	int			i;

	i = 0;
	while (cmd->redirs[i])
	{
		if (!init_fd(&fd_in, &fd_out, cmd->redirs[i], cmd))
			return (0);
		if (cmd->redirs[i]->op == OUT || cmd->redirs[i]->op == APPEND)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (cmd->redirs[i]->op == IN || cmd->redirs[i]->op == HEREDOC)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			if (cmd->redirs[i]->op == HEREDOC)
				unlink(cmd->redirs[i]->file);
		}
		i++;
	}
	return (1);
}
