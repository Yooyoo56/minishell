/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/12 12:03:00 by whazami          ###   ########.fr       */
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
	cmd->exit = 0;
}

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
	{
		printf("pwd: error retrieving current directory");
		printf(":getcwd: cannot access parent directories");
		printf(": No such file or directory\n");
	}
	else
		printf("%s\n", buf);
}

void	ft_exit(t_cmd *cmd)
{
	int	i;

	if (cmd->pid == -1)
		printf("exit\n");
	i = -1;
	if (cmd->args[0] == NULL)
		exit(0);
	while (cmd->args[0][++i])
	{
		if (!(ft_isdigit(cmd->args[0][i]) || (i == 0 && cmd->args[0][i] == '-'))
			|| ft_atold(cmd->args[0]) > LONG_MAX
			|| ft_atold(cmd->args[0]) < LONG_MIN)
		{
			print_err("exit", "%s: numeric argument required", cmd->args[0]);
			exit(255);
		}
	}
	if (cmd->args[1])
	{
		print_err("exit", "too many arguments", NULL);
		cmd->exit = 1;
		return ;
	}
	exit((long)ft_atold(cmd->args[0]));
}
