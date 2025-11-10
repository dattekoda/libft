/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:40:36 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/10 20:01:10 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

# define ATOF_BIAS 0b01111111111

// 指数部の桁数を取得する関数
int	get_exp(const char *nptr)
{
	int				exp;
	unsigned char	comp;

	exp = 0;
	while (ft_isdigit(*nptr))
	{
		exp++;
		nptr++;
	}
	if (!exp || *nptr != '.')
		return (exp);
	nptr++;
	comp = 0;
	while (ft_isdigit(*nptr))
	{
	}
}

double	ft_atof(const char *nptr)
{
	double				res;
	unsigned char		*res_ptr;
	double				base;
	int					exp;

	exp = get_exp(nptr);
	res = 0;
	res_ptr = (unsigned char *)&res;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		res_ptr[7] |= (1 << 7) * (*(nptr++) == '-');
	while (ft_isdigit(*nptr))
		res = res * 10 + *(nptr++) - '0';
	if (*nptr != '.')
		return (res);
	nptr++;
	base = 0.1;
	while (ft_isdigit(*nptr))
	{
		res += (*(nptr++) - '0') * base;
		base /= 10;
	}
	return (res);
}

#if 1
#include <stdlib.h>
int	main(int argc, char *argv[]) {
	double	my;
	double	real;

	if (argc == 1)
		return 1;
	my = ft_atof(argv[1]);
	real = atof(argv[1]);
	printf("ft\t:%f\n", my);
	printf("orig\t:%f\n", real);
	return (0);
}
#endif

#if 0

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void	print_specified_bytes_as_binary(unsigned char byte, int start, int end) {
	if (start < end || 7 < start || end < 0)
		return ;
	for (int bit = start; bit >= end; bit--) {
		if (byte & (1 << bit))
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
}

void	print_bytes_as_binary(unsigned char byte) {
	print_specified_bytes_as_binary(byte, 7, 0);
}

void	print_double_bits(void *ptr) {
	unsigned char	*bytes = (unsigned char *)ptr;
	size_t			i;

	i = 8;
	while (i != 0) {
		--i;
		if (i == 7) {
			print_specified_bytes_as_binary(bytes[i], 7, 7);
			write(1, ", ", 2);
			print_specified_bytes_as_binary(bytes[i], 6, 0);
		}
		else if (i == 6) {
			print_specified_bytes_as_binary(bytes[i], 7, 4);
			write(1, ", ", 2);
			print_specified_bytes_as_binary(bytes[i], 3, 0);
		}
		else
			print_bytes_as_binary(bytes[i]);
		if (i != 0 && i != 7)
			write(1, ", ", 2);
	}
	write(1, "\n", 1);
}

void	print_memory_bits(void *ptr, size_t size, bool big) {
	unsigned char	*bytes = (unsigned char *)ptr;

	if (big) {
		for (size_t i = size; i != 0; ) {
			print_bytes_as_binary(bytes[i]);
			if (i != 0)
				write(1, ", ", 2);
		}
	}
	else {
		for (size_t i = 0; i < size; i++) {
			print_bytes_as_binary(bytes[i]);
			if (i < size - 1)
				write(1, ", ", 2);
		}
	}
	write(1, "\n", 1);
}

int	main(int argc, char *argv[])
{
	bool	big = false;
	if (argc == 1)
		return 1;
	if (2 < argc)
		big = true;
	double	atof_res = atof(argv[1]);
	uint64_t	uint_val;

	memcpy(&uint_val, &atof_res, sizeof(double));
	printf("atof\t:%f\n", atof_res);
	printf("binary\t:0x%016llx\n", (unsigned long long)uint_val);
	print_double_bits(&uint_val);
	return 0;
}
#endif