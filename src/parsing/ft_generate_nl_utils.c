/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_nl_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 07:21:30 by whazami           #+#    #+#             */
/*   Updated: 2021/12/13 07:21:49 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strchri(char *s, char c, int start, int stop)
{
	int	i;

	i = start;
	while (stop == -1 || i < stop)
	{
		if (s[i] == c)
			return (&s[i]);
		if (!s[i])
			return (NULL);
		i++;
	}
	return (NULL);
}

void	erase_char(char *str, int index)
{
	int	i;

	i = index;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

char	get_non_printable(char c)
{
	if (c == ' ')
		return (ESPACE);
	if (c == '<')
		return (INF_);
	if (c == '>')
		return (SUP_);
	if (c == '|')
		return (PIPE_);
	return (c);
}

char	*ft_getenv(char *var_name, char **env)
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
			return (ft_substr(env[i], equal_pos + 1, ft_strlen(env[i])));
		}
		free(str_before_equal);
		i++;
	}
	return (ft_strdup(""));
}
