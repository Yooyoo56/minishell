#include "../../include/minishell.h"

/* Parsing errors:
 * si il y a un delimiteur a la fin de line (espaces compris) (ex : "cat >     ")
 * il ne doit pas y avoir plus de 2 caracteres sur un operateur (ex : "<<<" est une parsing error)
 * nombre impair de simple/double quotes
 * malloc size (if (ft_strlen(line) > SIZE_MAX) then error)
 * \ et ;
 * se renseigner si les caracteres qu'on ne doit pas gerer sont vus comme une erreur
 */

// delimiter : les pipes ne doivent pas coller.
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