/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:44:30 by ytak              #+#    #+#             */
/*   Updated: 2022/01/11 11:44:31 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_new_var_to_env_or_replace_it(char *var, char ***env, int redo)
{
	int		var_id;
	char	*tmp;

	var_id = get_var_id(var, *env);
	if (var_id == -1)
		add_var_to_env(var, env);
	else
	{
		if (redo)
		{
			tmp = ft_strjoin("OLD", (*env)[var_id]);
			add_new_var_to_env_or_replace_it(tmp, env, 0);
			free(tmp);
		}
		free((*env)[var_id]);
		(*env)[var_id] = ft_strdup(var);
	}
}

static void	ft_cd_first_arg(t_cmd *cmd, char ***env)
{
	char	*str;
	char	buf[1024];

	if (cmd->args[0])
	{
		if (chdir (cmd->args[0]) == -1)
		{
			if (access(cmd->args[0], F_OK) == 0)
				print_err("cd", "%s: Not a directory", cmd->args[0]);
			else
				print_err("cd", "%s: No such file or directory", cmd->args[0]);
			cmd->exit = 1;
		}
		else
		{
			getcwd(buf, sizeof(buf));
			str = ft_strjoin("PWD=", buf);
			add_new_var_to_env_or_replace_it(str, env, 1);
			free(str);
		}
	}
}

void	ft_cd(t_cmd *cmd, char ***env)
{
	char	*str;
	char	buf[1024];

	if (cmd->nom && cmd->args[0] == NULL)
	{
		str = ft_getenv("HOME", *env);
		if (str[0] == '\0')
		{
			print_err("cd", "HOME not set", NULL);
			cmd->exit = 1;
			free(str);
		}
		else
		{
			chdir(str);
			free(str);
			getcwd(buf, sizeof(buf));
			str = ft_strjoin("PWD=", buf);
			add_new_var_to_env_or_replace_it(str, env, 1);
			free(str);
		}
	}
	ft_cd_first_arg(cmd, env);
}
