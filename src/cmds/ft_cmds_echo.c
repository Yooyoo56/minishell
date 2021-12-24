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
	exit(cmd->exit);
}
