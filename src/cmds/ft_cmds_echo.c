/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:08:33 by ytak              #+#    #+#             */
/*   Updated: 2021/12/17 22:24:42 by whazami          ###   ########.fr       */
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
