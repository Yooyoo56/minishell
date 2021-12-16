/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:46:18 by ytak              #+#    #+#             */
/*   Updated: 2021/12/16 16:56:02 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Parsing errors:
 * si il y a un delimiteur a la fin d'une commande (espaces compris) (ex : "cat >     ") ==> ✅
 * il ne doit pas y avoir plus de 2 caracteres sur un operateur (ex : "<<<" est une parsing error) => ✅
 * nombre impair de simple/double quotes ==> ✅
 * malloc size (if (ft_strlen(line) > SIZE_MAX) then error)
 * \ et ; ==> ✅
 * se renseigner si les caracteres qu'on ne doit pas gerer sont vus comme une erreur
 */

//cheverons error: >>> or <<<
int	err_multiple_chevrons(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
			{
				if (line[i + 2] == '<' || line[i + 2] == '>')
				{
					printf("bash: syntax error near unexpected tken `newline' \n");
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

int	err_chevrons_reverse(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			if (line[i + 1] == '>')
			{
				printf("bash: syntax error near unexpected tken `newline' \n");
				return (1);
			}
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '<')
			{
				printf("bash: syntax error near unexpected tken `newline' \n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	err_pipes(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
			{
				printf("bash: syntax error near unexpected token `||'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	err_odd_double_quotes(const char *line)
{
	int	i;
	int	cpt;
	
	i = 0;
	cpt = 0;
	while (line[i])
	{
		if (line[i] == '"')
			cpt++;
		i++;
	}
	if (cpt % 2 == 1)
	{
//		line = readline("dquote> ");
		printf("Error! quotes error!\n");
//		free((void *)line);
		return (1);
	}
	return (0);
}

int	err_odd_simple_quotes(const char *line)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			cpt++;
		i++;
	}
	if (cpt % 2 == 1)
	{
		printf("Error! quotes error!\n");
		return (1);
	}
	return (0);
}

int	err_pipe_space(const char *line)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(line);
	
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|' || line[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	err_combine_quotes(const char *line)
{
	int i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote = line[i];
			i++;
			if (line[i] == '\0')
			{
				printf("🎃 Yoohooo you found out the error\n");
				return (1);
			}
			while (line[i])
			{
				if (line[i] == quote)
					break ;
				if (line[i + 1] == '\0')
				{
					printf("🎃 Yoohooo you found out the error\n");
					return (1);
				}
				i++;
			}
		}
		if (line[i])
			i++;
	}
	return (0);
}




int	err_chevrons_space(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '>' || line[i + 1] == '<')
				i++;
			i++;
			while (line[i] == ' ')
				i++;
			if (is_operator(line[i]) || line[i] == '\0')
			{
				printf("bash: syntax error near unexpected tken `newline' \n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// if you see \  => error
int	err_slash(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			printf("Error! no \\ in the line\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// if you see ; => error
int	err_semicolon(const char *line)
{
	int i; 
	
	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
		{
			printf("Error! no ; in the line\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing_error(const char *line)
{
	//malloc error
	if (ft_strlen(line) > 1000000000)
	{
		printf("Error! Malloc error! Line too long\n");
		return (1);
	}
	if (err_multiple_chevrons(line))
		return (1);
	if (err_chevrons_reverse(line))
		return (1);
	if (err_pipes(line))
		return (1);
	if (err_odd_double_quotes(line))
		return (1);
	if (err_odd_simple_quotes(line))
		return (1);
	if (err_slash(line))
		return (1);
	if (err_semicolon(line))
		return (1);
	if (err_chevrons_space(line))
		return (1);
	if (err_pipe_space(line))
		return (1);
	if (err_combine_quotes(line))
		return (1);
	return (0);
}
/*
// need to create ||| or <<< or >>>>>>>> =====> error!!
// /!\ Attention : '><' et '<>' sont des erreurs (espace entre eux inclus)
int	parsing_error(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
		{
			i++;
			while (ft_isspace(line[i]))
				i++;
			if (is_operator(line[i]))
			{
				printf("Error! Parsing error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
*/
