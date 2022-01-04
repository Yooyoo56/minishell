/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/03 16:40:43 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	there_is_only_char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 0;
	while (cmd->args[i] != NULL && cmd->args[i][0] == '-'
		&& there_is_only_char_in_str('n', cmd->args[i] + 1))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag_n)
		printf("\n");
}

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
	{
		printf("pwd: error retrieving curremt directory");
		printf(":getcwd: cannot access parent directories");
		printf(": No such file or directory\n");
	}
	else
		printf("%s\n", buf);
}

void ft_cd(t_cmd *cmd)
{
	if (cmd->nom)
	{
		chdir(getenv("HOME"));
		printf("cd: %s\n", getenv("HOME"));
	}
/*	if (strcmp(cmd->nom, "cd") == 0)
	{
		chdir(getenv("HOME"));
		printf("cd: %s\n", getenv("HOME"));
	}*/
	if (cmd->args[0])
	{
		chdir(getenv(cmd->args[0]));
		printf("cd dir:%s\n", getenv(cmd->args[0]));
	}
}

