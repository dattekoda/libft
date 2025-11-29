/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:35:36 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/18 17:06:59 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <endian.h>

void	print_specified_bytes_as_binary(unsigned char byte, int start, int end);
void	print_bytes_as_binary(unsigned char byte);
void	print_double_bits(void *ptr);

double	ft_infinity(void)
{
	double			a;
	unsigned char	*a_ptr;

	a = 0;
	a_ptr = (unsigned char *)&a;
	if (__BYTE_ORDER == __BIG_ENDIAN)
	{
		a_ptr[0] = 0x7F;
		a_ptr[1] = 0xF0;
	}
	else
	{
		a_ptr[7] = 0x7F;
		a_ptr[6] = 0xF0;
	}
	return (a);
}

double	ft_nan(void)
{
	double			a;
	unsigned char	*a_ptr;

	a = 0;
	a_ptr = (unsigned char *)&a;
	if (__BYTE_ORDER == __BIG_ENDIAN)
	{
		a_ptr[0] = 0x7F;
		a_ptr[1] = 0xF8;
	}
	else
	{
		a_ptr[7] = 0x7F;
		a_ptr[6] = 0xF8;
	}
	return (a);
}

int	main(int argc, char *argv[]) {
	double			a;
	char			*arg_p;

	if (argc == 1)
		return 1;
	a = strtod(argv[1], &arg_p);
	printf("%f\n", a);
	print_double_bits(&a);
	printf("%s\n", arg_p);
}

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