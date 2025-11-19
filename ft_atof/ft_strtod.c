/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:33:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/19 19:20:55 by khanadat         ###   ########.fr       */
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

void	set_ten_in_limb(mp_limb_t *ten_in_limb)
{
	const mp_limb_t	_ten_in_limb[MAX_DIG_PER_LIMB + 1] = {
		1,
		10,
		100,
		1000,
		10000,
		100000L,
		1000000L,
		10000000L,
		100000000L,
		1000000000ULL,
		10000000000ULL,
		100000000000ULL,
		1000000000000ULL,
		10000000000000ULL,
		100000000000000ULL,
		1000000000000000ULL,
		10000000000000000ULL,
		100000000000000000ULL,
		1000000000000000000ULL,
		10000000000000000000ULL
	};

	ft_memmove(ten_in_limb, _ten_in_limb, \
		sizeof(mp_limb_t) * (MAX_DIG_PER_LIMB + 1));
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
