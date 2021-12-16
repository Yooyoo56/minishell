/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:05:32 by whazami           #+#    #+#             */
/*   Updated: 2021/12/16 12:25:22 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;

	if (malloc(100000000000000) == NULL)
	{
		printf("malloc error!\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		printf("arg %d: %s\n", i - 1, argv[i]);
		i++;
	}
	return (0);
}
