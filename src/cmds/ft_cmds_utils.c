/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:10:42 by whazami           #+#    #+#             */
/*   Updated: 2021/12/16 19:10:44 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_name_is(t_cmd *cmd, char *str)
{
	return (ft_strncmp(cmd->nom, str, ft_strlen(cmd->nom)) == 0);
}
