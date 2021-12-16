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

int	get_var_id(char *var_name, char **env)
{
	int		i;
	int		equal_pos;
	char	*str_before_equal;

	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		str_before_equal = ft_substr(env[i], 0, equal_pos);
		if (ft_strncmp(str_before_equal, var_name,
				ft_strlen(var_name) + ft_strlen(str_before_equal)) == 0)
		{
			free(str_before_equal);
			return (i);
		}
		free(str_before_equal);
		i++;
	}
	return (-1);
}

int	identifier_is_valid(char *identifier)
{
	int	i;

	if (ft_isdigit(identifier[0]) || ft_strlen(identifier) == 0)
		return (0);
	i = 0;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
