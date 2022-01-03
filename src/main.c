/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:41:05 by whazami           #+#    #+#             */
/*   Updated: 2022/01/03 13:09:12 by ytak             ###   ########.fr       */
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
	line = readline("$> ");
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		if (!is_empty(line))
		{
			add_history(line);
			cmds = parsing(line, env);
			if (cmds)
			{
				//print_cmds(cmds);
				manage_cmds(cmds, &env);
				free_cmds(cmds);
			}
		}
		free(line);
		line = readline("$> ");
	}
	free(line);
	free_2d_array((void **)env);
	system("leaks minishell");
	return (0);
}
