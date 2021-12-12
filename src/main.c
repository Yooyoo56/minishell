/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:41:05 by whazami           #+#    #+#             */
/*   Updated: 2021/12/04 02:41:07 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char		*line;

	print_header();
	line = readline("$> ");
	while (ft_strncmp(line, "exit", ft_strlen(line)) != 0 || !ft_strlen(line))
	{
		if (ft_strlen(line))
		{
			add_history(line);
			parsing(line);
		}
		free(line);
		line = readline("$> ");
	}
	free(line);
	//system("leaks minishell");
	return (0);
}
