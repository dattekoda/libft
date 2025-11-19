/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_utils0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:05:02 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/19 18:10:06 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_strtod_define.h"
#include <endian.h>

int	is_hexalpha(int c)
{
	return (('a' <= c && c <= 'f') \
		|| ('A' <= c && c <= 'F'));
}

int	tod_is_valid_num(t_strtod *tod)
{
	return (ft_isdigit(*(tod->cp)) \
		|| (tod->base == 16 && is_hexalpha(*(tod->cp))));
}

static void	set_negative(t_strtod *tod)
{
	unsigned char	*ret_ptr;

	ret_ptr = (unsigned char *)&tod->ret;
	if (tod->negative)
	{
		if (__BYTE_ORDER == __LITTLE_ENDIAN)
			ret_ptr[7] |= 0x80;
		else
			ret_ptr[0] |= 0x80;
	}
}

#include <stdio.h>
static void	checker_tod(t_strtod *tod) {
	printf("negative\t: %d\n", tod->negative);
	printf("base\t\t: %d\n", tod->base);
	printf("cp\t\t: %s\n", tod->cp);
	printf("int_no\t\t: %zu\n", tod->int_no);
	printf("dig_no\t\t: %zu\n", tod->dig_no);
	printf("exp\t\t: %ld\n", tod->exponent);
	printf("start_of_digits\t: %s\n", tod->start_of_digits);
	printf("lead_zero\t: %zu\n", tod->lead_zero);
}

double	set_endptr(t_strtod *tod, char **endptr)
{
	if (endptr)
		*endptr = (char *)tod->cp;
	set_negative(tod);
	checker_tod(tod);
	return (tod->ret);
}
