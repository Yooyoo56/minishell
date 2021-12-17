/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:08:33 by ytak              #+#    #+#             */
/*   Updated: 2021/12/17 16:44:42 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
    // if there is one argument, no space !
    // printf("%s", cmd->args[i++]);
	///if there - => print - argument
	if (cmd->args)
		while (cmd->args[i])
			printf("%s ", cmd->args[i++]);
	if (cmd->flag == NULL)
		printf("\n");
	else if (ft_strncmp(cmd->flag, "-n", ft_strlen(cmd->flag)) != 0)
		printf("\n");
}
