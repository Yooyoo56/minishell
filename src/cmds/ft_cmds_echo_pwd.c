/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/06 17:26:46 by ytak             ###   ########.fr       */
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

void	ft_cd(t_cmd *cmd, char **env)
{
	char	*str;

	str = ft_getenv("HOME", env);
	if (cmd->nom && cmd->args[0] == NULL)
	{
		if (str[0] == '\0')
		{
			print_err("cd", "HOME not set", NULL);
			cmd->exit = 1;
		}
		else
			chdir(str);
	}
	if (cmd->args[0])
	{
		if (chdir (cmd->args[0]) == -1)
		{
			if (access(cmd->args[0], F_OK) == 0)
				print_err("cd", "%s: Not a directory", cmd->args[0]);
			else
				print_err("cd", "%s: No such file or directory", cmd->args[0]);
			cmd->exit = 1;
		}
	}
	free(str);
}

void	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[0] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	while (cmd->args[0][i])
	{
		if (!(ft_isdigit(cmd->args[0][i++])))
		{
			printf("exit\n");
			print_err("exit", "%s: numeric argument required", cmd->args[0]);
			exit(255);
		}
	}
	if (cmd->args[1])
	{
		printf("exit\n");
		print_err("exit", "too many arguments", NULL);
		exit(1);
	}
	printf("exit\n");
	exit(ft_atoi(cmd->args[0]));
}
