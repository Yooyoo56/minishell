/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:01:44 by whazami           #+#    #+#             */
/*   Updated: 2021/12/21 22:45:04 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	get_var_id(char *var, char **env)
{
	int		i;
	int		equal_pos;
	char	*str_before_equal;

	i = 0;
	equal_pos = ft_strchr(var, '=') - var;
	var = ft_substr(var, 0, equal_pos);
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		str_before_equal = ft_substr(env[i], 0, equal_pos);
		if (ft_strcmp(str_before_equal, var) == 0)
		{
			free(var);
			free(str_before_equal);
			return (i);
		}
		free(str_before_equal);
		i++;
	}
	free(var);
	return (-1);
}

int	identifier_is_valid(char *identifier, int is_export)
{
	int	i;

	if (ft_isdigit(identifier[0]) || ft_strlen(identifier) == 0)
		return (0);
	i = 0;
	while (identifier[i])
	{
		if (is_export && identifier[i] == '=' && i > 0)
			return (1);
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_sorted_env(char **env)
{
	int		i[3];
	char	**c;

	c = (char **)ft_calloc(1, sizeof(char *));
	*i = -1;
	while (env[++*i])
	{
		c = ft_realloc(c, (*i + 1) * sizeof(char *), (*i + 2) * sizeof(char *));
		c[*i] = ft_strdup(env[*i]);
	}
	i[1] = 0;
	while (++i[1] < *i)
	{
		i[2] = i[1];
		while (++i[2] < *i)
			if (ft_strcmp(c[i[1]], c[i[2]]) < 0)
				ft_swap(&c[i[1]], &c[i[2]], sizeof(char *));
	}
	while (--i[1])
		printf("declare -x %.*s%c%c%s%c\n", (int)(ft_strchr_end(c[i[1]], '=')
				- c[i[1]]), c[i[1]], '=' * (!!ft_strchr(c[i[1]], '=')),
			'"' * (!!ft_strchr(c[i[1]], '=')), ft_strchr_end(c[i[1]], '=')
			+ !!ft_strchr(c[i[1]], '='), '"' * (!!ft_strchr(c[i[1]], '=')));
	free_2d_array((void **)c);
}

void	add_var_to_env(char *var, char ***env)
{
	int		size;
	char	**tmp;

	tmp = ft_calloc(2, sizeof(char *));
	size = 0;
	while ((*env)[size])
	{
		tmp = ft_realloc(tmp, (size + 2) * sizeof(char *),
				(size + 3) * sizeof(char *));
		tmp[size] = ft_strdup((*env)[size]);
		size++;
	}
	tmp[size] = ft_strdup(var);
	free_2d_array((void **)*env);
	*env = tmp;
}
