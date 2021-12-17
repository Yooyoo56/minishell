/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:02:56 by ytak              #+#    #+#             */
/*   Updated: 2021/12/16 13:02:57 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	// if there is one argument, no space !
	// printf("%s", cmd->args[i++]);

	//if there - => print - argument
	while (cmd->args[i])
		printf("%s ", cmd->args[i++]);
	if (cmd->flag == NULL)
		printf("\n");
	else if (ft_strncmp(cmd->flag, "-n", ft_strlen(cmd->flag)) != 0)
		printf("\n");
}

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmd_name_is(cmds[i], "echo"))
			ft_echo(cmds[i]);
		else if (cmd_name_is(cmds[i], "env"))
			ft_env(*env);
		else if (cmd_name_is(cmds[i], "unset"))
			ft_unset(cmds[i], *env);
		else if (cmd_name_is(cmds[i], "export"))
			ft_export(cmds[i], env);
		i++;
	}
}
