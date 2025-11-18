#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	main(int argc, char *argv[])
{
	bool	is_minus = false;

	if (argc == 1)
		return 1;
	int	upper = atoi(argv[1]);
	if (upper < 0) {
		is_minus = true;
		upper *= (-1);
	}
	if (is_minus) {
		printf("0.");
		upper--;
	}
	else
		printf("1");
	for (int i = 0; i < upper; i++) {
		printf("0");
	}
	if (is_minus)
		printf("1");
	printf("e");
	if (is_minus)
		printf("%d", upper + 1);
	else
		printf("%d", -upper);
}
