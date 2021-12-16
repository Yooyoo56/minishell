/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:41:05 by whazami           #+#    #+#             */
/*   Updated: 2021/12/16 10:55:42 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	handler(int sig)
{
	if (sig == SIGINT)
		printf("haha\n");
}
*/
int	main(void)
{
	char		*line;
	t_cmd		**cmds;

	print_header();
	line = readline("$> ");
//	signal(SIGINT, handler);
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		//line = readline("$> ");
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
//	system("leaks minishell");
	return (0);
}
