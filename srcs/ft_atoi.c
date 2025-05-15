/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 06:18:52 by khanadat          #+#    #+#             */
/*   Updated: 2025-04-26 06:18:52 by khanadat         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' '
		|| ('\t' <= c && c <= '\r'))
		return (8192);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	result = 0;
	while (nptr[i] && '0' <= nptr[i]
		&& nptr[i] <= '9')
		result = 10 * result + (nptr[i++] - '0');
	return (result * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char* argv[])
{
	if (argc == 1) return 0;
	printf("original: %s\n", argv[1]);
	printf("atoi:     %d\n", atoi(argv[1]));
	printf("ft_atoi:  %d\n", ft_atoi(argv[1]));
	return 0;
}*/