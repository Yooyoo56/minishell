/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/03 14:03:20 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->flag != NULL && ft_strcmp(cmd->flag, "-n") != 0)
	{
		printf("%s", cmd->flag);
		if (cmd->args[0])
			printf(" ");
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (cmd->flag == NULL)
		printf("\n");
	else if (ft_strcmp(cmd->flag, "-n") != 0)
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
