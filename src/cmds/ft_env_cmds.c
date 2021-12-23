/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:59:52 by whazami           #+#    #+#             */
/*   Updated: 2021/12/17 21:00:06 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	exit(0);
}

void	ft_unset(t_cmd *cmd, char **env)
{
	int	i;
	int	j;
	int	var_id;

	i = 0;
	while (cmd->args[i])
	{
		var_id = get_var_id(cmd->args[i], env);
		if (!identifier_is_valid(cmd->args[i], 0))
			printf("bash: unset: `%s': not a valid identifier\n",
				cmd->args[i]);
		else if (var_id != -1 && ft_strncmp(cmd->args[i], "_",
				ft_strlen(cmd->args[i])))
		{
			free(env[var_id]);
			j = var_id;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
		}
		i++;
	}
}

void	ft_export(t_cmd *cmd, char ***env)
{
	int		i;
	int		var_id;

	if (cmd->args[0] == NULL)
		return ((void)print_sorted_env(*env));
	i = 0;
	while (cmd->args[i])
	{
		if (identifier_is_valid(cmd->args[i], 1))
		{
			var_id = get_var_id(cmd->args[i], *env);
			if (var_id == -1)
				add_var_to_env(cmd->args[i], env);
			else if (ft_strchr(cmd->args[i], '='))
			{
				free((*env)[var_id]);
				(*env)[var_id] = ft_strdup(cmd->args[i]);
			}
		}
		else
			printf("bash: export: `%s': not a valid identifier\n",
				cmd->args[i]);
		i++;
	}
}
