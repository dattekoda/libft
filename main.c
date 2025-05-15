#include "libft.h"
#include <bsd/string.h>
#include <stdio.h>
int	main(void) {
	char dst[10] = "\0";
	char dstorigin[10] = "\0";
	char src[100] = "ohayo sayonara ohayo sayonara ohayo sayonara";
	ft_strlcpy(NULL, src, 8);
	// strlcpy(NULL, src, 8);
	printf("ft: %s\n", dst);
	printf("or: %s\n", dstorigin);
	return 0;
}