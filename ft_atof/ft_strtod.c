/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:33:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 06:55:55 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "ft_strtod_set_utils.h"
#include <stddef.h>
#include <stdbool.h>
#include <endian.h> // big endian or little

#include <stdio.h>

int	set_tod(t_strtod *tod, const char *nptr)
{
	ft_bzero(tod, sizeof(t_strtod));
	tod->cp = nptr;
	skip_sp_set_negative(tod);
	if (is_inf(tod) || is_nan(tod))
		return (IS_OVER_FLOW);
	set_base(tod);
	tod->start_of_digits = tod->cp;
	scan_digits(tod);
	if (parse_exp(tod))
		return (IS_OVER_FLOW);
	normalize_exponent(tod);
	return (NOT_OVER_FLOW);
}

int	_mpn_mul_1(t_mpn *mpn, mp_limb_t limb)
{
	__uint128_t	cy;
	size_t		i;

	i = 0;
	cy = 0;
	while (i < mpn->size)
	{
		cy = limb * mpn->limbs[i] + cy;
		mpn->limbs[i] = 0x0000FFFF & cy;
		cy = cy >> 64;
		i++;
	}
	if (cy && i < MPNSIZE_MAX)
	{
		mpn->limbs[i] = 0x0000FFFF & cy;
		mpn->size++;
	}
	else if (cy)
		return (IS_OVER_FLOW);
	return (NOT_OVER_FLOW);
}

void	_mpn_add_1(t_mpn *mpn, mp_limb_t limb)
{
}

double	ft_strtod(const char *nptr, char **endptr)
{
	t_strtod	tod;

	if (set_tod(&tod, nptr))
		return (set_endptr(&tod, endptr));
	return (set_endptr(&tod, endptr));
}

void	print_tod_num(t_strtod *tod)
{
	mp_size_t	i = 0;

	printf("size: %ld\n", tod->num.size);
	while (i < tod->num.size) {
		printf("%lu", tod->num.limbs[i++]);
	}
}

int	main(int argc, char *argv[])
{
	double	tmp;
	char	*ar;

	if (argc == 1)
		return 1;
	tmp = ft_strtod(argv[1], &ar);
	printf("%f\n", tmp);
	// printf("%s\n", ar);
}
