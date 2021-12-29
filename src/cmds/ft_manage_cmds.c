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
		else if (cmd_name_is(cmds[i], "echo"))
			ft_echo(cmds[i]);
		i++;
	}
}
