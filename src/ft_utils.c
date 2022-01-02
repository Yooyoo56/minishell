/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:54:35 by whazami           #+#    #+#             */
/*   Updated: 2021/12/17 22:34:58 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_2d_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->nom)
			free(cmds[i]->nom);
		free_2d_array((void **)cmds[i]->args);
		j = 0;
		while (cmds[i]->redirs && cmds[i]->redirs[j])
		{
			free(cmds[i]->redirs[j]->file);
			free(cmds[i]->redirs[j]);
			j++;
		}
		free(cmds[i]->redirs);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	is_empty(char *str)
{
	int	i;

	if (ft_strlen(str) == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* if you put '%s' in the error string, it will be replaced by the
 * arg string (obviously it's optional). */
int	print_err(char *cmd_name, char *error, char *arg)
{
	char		*str;
	char		*cp;
	long int	prc_pos;

	str = ft_strjoin("bash: ", cmd_name);
	ft_strapp(&str, ": ");
	prc_pos = ft_strchr(error, '%') - error;
	cp = ft_strdup(error);
	while (prc_pos >= 0)
	{
		if (error[prc_pos + 1] == 's')
		{
			cp = ft_realloc(cp, ft_strlen(cp), ft_strlen(cp) + ft_strlen(arg));
			ft_strlcpy(&cp[prc_pos], arg, ft_strlen(arg) + 1);
			ft_strlcpy(&cp[prc_pos + ft_strlen(arg)], &error[prc_pos + 2],
				ft_strlen(error));
		}
		prc_pos = ft_strchri(error, '%', prc_pos + 1, ft_strlen(error)) - error;
	}
	ft_strapp(&str, cp);
	ft_strapp(&str, "\n");
	prc_pos = ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	free(cp);
	return (prc_pos);
}

static void	print_redir(t_redir *redir)
{
	printf("op: ");
	if (redir->op == IN)
		printf("<");
	else if (redir->op == HEREDOC)
		printf("<<");
	else if (redir->op == OUT)
		printf(">");
	else if (redir->op == APPEND)
		printf(">>");
	printf(", file: %s}", redir->file);
}

void	print_cmds(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		printf("{name: %s", cmds[i]->nom);
		j = 0;
		while (cmds[i]->args[j])
		{
			printf(", arg %d: %s", j, cmds[i]->args[j]);
			j++;
		}
		j = 0;
		while (cmds[i]->redirs[j])
		{
			printf(", {redir %d: ", j);
			print_redir(cmds[i]->redirs[j]);
			j++;
		}
		printf("}\n");
		i++;
	}
}

void	print_header(void)
{
	printf("\x1B[33m");
	printf(":.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:\n");
	printf(":                      |\\      _,,,---,,_               :\n");
	printf(":   whazami      ZZZzz /,`.-'`'    -.  ;-;;,_           :\n");
	printf(":   ytak              |,4-  ) )-,_. ,\\ (  `'-'          :\n");
	printf(":                    '---''(_/--'  `-'\\_)               :\n");
	printf(":                                                       :\n");
	printf(":                 ,--.         ,--.            ,--.,--. :\n");
	printf(":  ,---. ,--,--.,-'  '-. ,---. |  ,---.  ,---. |  ||  | :\n");
	printf(": | .--'' ,-.  |'-.  .-'(  .-' |  .-.  || .-. :|  ||  | :\n");
	printf(": \\ `--.\\ '-'  |  |  |  .-'  `)|  | |  |\\   --.|  ||  | :\n");
	printf(":  `---' `--`--'  `--'  `----' `--' `--' `----'`--'`--' :\n");
	printf(":.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:\n");
}
