/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:54:35 by whazami           #+#    #+#             */
/*   Updated: 2021/12/08 17:54:37 by whazami          ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->nom)
		free(cmd->nom);
	if (cmd->flag)
		free(cmd->flag);
	free_2d_array((void **)cmd->args);
	i = 0;
	while (cmd->redirs[i])
	{
		free(cmd->redirs[i]->file);
		free(cmd->redirs[i]);
		i++;
	}
	free(cmd->redirs);
}

void	print_cmd(t_cmd cmd)
{
	int	i;

	printf("{name: %s", cmd.nom);
	if (cmd.flag)
		printf(", flag: %s", cmd.flag);
	i = 0;
	if (cmd.args[i])
		printf(", ");
	while (cmd.args[i])
	{
		printf("arg %d: %s", i, cmd.args[i]);
		if (cmd.args[i + 1])
			printf(", ");
		i++;
	}
	i = 0;
	while (cmd.redirs[i])
	{
		printf(", redirs[%d]: op: ", i);
		if (cmd.redirs[i]->op == INF)
			printf("<");
		else if (cmd.redirs[i]->op == DOUBLE_INF)
			printf("<<");
		else if (cmd.redirs[i]->op == SUP)
			printf(">");
		else if (cmd.redirs[i]->op == DOUBLE_SUP)
			printf(">>");
		printf(", file: %s", cmd.redirs[i]->file);
		i++;
	}
	printf("}\n");
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