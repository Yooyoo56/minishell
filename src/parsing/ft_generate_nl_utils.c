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

	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=') - env[i];
		if (ft_strncmp(env[i], var_name, equal_pos) == 0)
			return (ft_substr(env[i], equal_pos + 1, ft_strlen(env[i])));
		i++;
	}
	return (ft_strdup(""));
}