/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:41:05 by whazami           #+#    #+#             */
/*   Updated: 2021/12/13 17:58:43 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char		*line;
	t_cmd		**cmds;

	print_header();
	line = readline("$> ");
	while (ft_strncmp(line, "exit", 4) != 0 || !ft_strlen(line))
	{
		if (ft_strlen(line))
		{
			add_history(line);
			cmds = parsing(line);
			if (cmds)
			{
				print_cmds(cmds);
				free_cmds(cmds);
			}
		}
		free(line);
		line = readline("$> ");
	}
	free(line);
	//system("leaks minishell");
	return (0);
}
