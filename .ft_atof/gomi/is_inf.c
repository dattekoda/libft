#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

double	ft_infinity(void)
{
	double	a;
	unsigned char	*a_ptr;

	ft_bzero(&a, sizeof(double));
	a_ptr = (unsigned char *)&a;
	a_ptr[7] = 0x7F;
	a_ptr[6] = 0xF0;
	return (a);
}

bool	is_inf(const char **str)
{
	static const char	*inf_pattern = "infinity";
	size_t				i;

	i = 0;
	while ((*str)[i] && i < 3)
	{
		if (ft_tolower((*str)[i]) != inf_pattern[i])
			break ;
		i++;
	}
	if (i != 3)
		return (false);
	while ((*str)[i] && i < 8)
	{
		if (ft_tolower((*str)[i]) != inf_pattern[i])
			break ;
		i++;
	}
	*str += 3;
	if (i == 8)
		*str += 5;
	return (true);
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return 1;
	char	*ar = argv[1];
	if (is_inf((const char **)&ar))
		printf("inf\n");
	else
		printf("not_inf\n");
	printf("%s\n", ar);
	return 0;
}