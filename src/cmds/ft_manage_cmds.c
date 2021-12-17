/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:02:56 by ytak              #+#    #+#             */
/*   Updated: 2021/12/17 16:42:07 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    manage_cmds(t_cmd **cmds)
{
    int i;

    i = 0;
    while (cmds[i])
    {
		if (cmds[i]->nom)
		{
			if (ft_strncmp(cmds[i]->nom, "echo", ft_strlen(cmds[i]->nom)) == 0)
				ft_echo(cmds[i]);
		}
        i++;
    }
}
