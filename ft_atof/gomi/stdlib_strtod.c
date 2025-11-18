#include <stdio.h>
#include <stdlib.h>
int	main(int argc, char *argv[])
{
	if (argc == 1)
		return 1;
	char	*nyos;
	fprintf(stderr, "%f\n", strtod(argv[1], &nyos));
	fprintf(stderr, "%s\n", nyos);
}