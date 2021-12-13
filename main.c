#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		printf("arg %d: %s\n", i - 1, argv[i]);
		i++;
	}
	return (0);
}
