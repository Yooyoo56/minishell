/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:41:05 by whazami           #+#    #+#             */
/*   Updated: 2022/01/10 14:54:07 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_cmd		**cmds;

	(void)argc;
	(void)argv;
	init_env(&env);
	print_header();
	while (42)
	{
		cmd_signal();
		line = readline("$> ");
		if (!is_empty(line))
		{
			add_history(line);
			cmds = parsing(line, env);
			if (cmds)
			{
				manage_cmds(cmds, &env);
				free_cmds(cmds);
			}
		}
		free(line);
	}
	free_2d_array((void **)env);
	return (0);
}
