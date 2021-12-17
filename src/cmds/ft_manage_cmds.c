/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:02:56 by ytak              #+#    #+#             */
/*   Updated: 2021/12/16 13:02:57 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	// if there is one argument, no space !
	// printf("%s", cmd->args[i++]);

	//if there - => print - argument
	while (cmd->args[i])
		printf("%s ", cmd->args[i++]);
	if (cmd->flag == NULL)
		printf("\n");
	else if (ft_strncmp(cmd->flag, "-n", ft_strlen(cmd->flag)) != 0)
		printf("\n");
}

static void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

static void	ft_unset(t_cmd *cmd, char **env)
{
	int	i;
	int	j;
	int	var_id;

	i = 0;
	while (cmd->args[i])
	{
		var_id = get_var_id(cmd->args[i], env);
		if (var_id != -1 && ft_strncmp(cmd->args[i], "_",
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
		else if (!identifier_is_valid(cmd->args[i], 0))
			printf("bash: unset: `%s': not a valid identifier\n",
				cmd->args[i]);
		i++;
	}
}

static void	ft_export(t_cmd *cmd, char ***env)
{
	int		i;
	int		var_id;
	int		size;
	char	**tmp;

	if (cmd->args[0] == NULL)
		return (print_sorted_env(*env));
	i = 0;
	while (cmd->args[i])
	{
		if (identifier_is_valid(cmd->args[i], 1))
		{
			var_id = get_var_id(cmd->args[i], *env);
			if (var_id == -1)
			{
				tmp = ft_calloc(1, sizeof(char *));
				size = 0;
				while ((*env)[size])
				{
					tmp = ft_realloc(tmp, (size + 2) * sizeof(char *),
						(size + 3) * sizeof(char *));
					tmp[size] = ft_strdup((*env)[size]);
					size++;
				}
				tmp[size] = ft_strjoin("\177", cmd->args[i]);
				free_2d_array((void **)*env);
				*env = tmp;
			}
			else
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

void	manage_cmds(t_cmd **cmds, char ***env)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmd_name_is(cmds[i], "echo"))
			ft_echo(cmds[i]);
		else if (cmd_name_is(cmds[i], "env"))
			ft_env(*env);
		else if (cmd_name_is(cmds[i], "unset"))
			ft_unset(cmds[i], *env);
		else if (cmd_name_is(cmds[i], "export"))
			ft_export(cmds[i], env);
		i++;
	}
}
