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

void	init_env(char ***env)
{
	char	**tmp;
	int		size;
	
	tmp = ft_calloc(1, sizeof(char *));
	size = 0;
	while ((*env)[size])
	{
		tmp = ft_realloc(tmp, (size + 1) * sizeof(char *),
			(size + 2) * sizeof(char *));
		tmp[size] = ft_strdup((*env)[size]);
		size++;
	}
	*env = tmp;
}

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
