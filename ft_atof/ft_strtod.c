/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:33:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/18 22:09:46 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include <stddef.h>
#include <stdbool.h>
#include <endian.h> // big endian or little

#include <stdio.h>

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

void	set_base(t_strtod *tod)
{
	bool		has_hex;
	const char	*peek;

	tod->base = 10;
	if (!(*(tod->cp) == '0' \
		&& (ft_tolower(*(tod->cp + 1)) == 'x')))
		return ;
	peek = tod->cp + 2;
	has_hex = (bool)((ft_isdigit(*peek) \
		|| is_hexalpha(*peek)));
	if (has_hex == false && *peek == '.')
	{
		peek++;
		has_hex = (bool)((ft_isdigit(*peek) \
		|| is_hexalpha(*peek)));
	}
	if (!has_hex)
		return ;
	tod->base = 16;
	tod->cp += 2;
}

bool	count_zeros(t_strtod *tod)
{
	size_t	i;
	bool	already_point;

	i = 0;
	already_point = false;
	while (*(tod->cp) == '0')
		(tod->cp)++;
	if (*(tod->cp) == '.')
	{
		already_point = true;
		(tod->cp)++;
	}
	while (*(tod->cp) == '0')
	{
		(tod->cp)++;
		(tod->lead_zero)++;
		(tod->dig_no)++;
	}
	return (already_point);
}

void	scan_digits(t_strtod *tod)
{
	bool	already_point;

	already_point = count_zeros(tod);
	while (!already_point && tod_is_valid_num(tod))
	{
		(tod->cp)++;
		(tod->int_no)++;
		(tod->dig_no)++;
	}
	if (!already_point && *(tod->cp) == '.')
		(tod->cp)++;
	while (tod_is_valid_num(tod))
	{
		(tod->cp)++;
		(tod->dig_no)++;
	}
}

void	set_exp_limit(intmax_t *exp_limit, t_strtod *tod, bool sign_exp)
{
	*exp_limit = 0;
	if (tod->base == 10)
	{
		if (sign_exp)
			*exp_limit = -MIN_10_EXP + MANT_DIG + tod->int_no;
		else if (0 < tod->int_no)
			*exp_limit = MAX_10_EXP - tod->int_no + 1;
		else
			*exp_limit = MAX_10_EXP + tod->lead_zero + 1;
	}
	else
	{
		if (sign_exp)
			*exp_limit = -MIN_EXP + MANT_DIG + tod->int_no;
		else if (0 < tod->int_no)
			*exp_limit = MAX_EXP - 4 * (intmax_t)tod->int_no;
		else if (tod->lead_zero == (size_t)(-1))
			*exp_limit = MAX_EXP + 3;
		else
			*exp_limit = MAX_EXP + 4 * (intmax_t)tod->lead_zero + 3;
	}
	if (*exp_limit < 0)
		*exp_limit = 0;
}

int	is_overflow(t_strtod *tod, intmax_t exp_limit, bool sign_exp)
{
	if (exp_limit / 10 < tod->exponent \
		|| (tod->exponent == exp_limit / 10 \
			&& (*(tod->cp) - '0') > exp_limit % 10))
	{
		if (!sign_exp)
			tod->ret = ft_infinity();
		return (IS_OVER_FLOW);
	}
	return (NOT_OVER_FLOW);
}

// if overflow return 1
int	parse_exp(t_strtod *tod)
{
	bool		sign_exp;
	intmax_t	exp_limit;

	sign_exp = false;
	if (tod->base == 10 && ft_tolower(*(tod->cp)) == 'e')
		(tod->cp)++;
	else if (tod->base == 16 && ft_tolower(*(tod->cp) == 'p'))
		(tod->cp)++;
	else
		return (NOT_OVER_FLOW);
	if (*(tod->cp) == '+' || *(tod->cp) == '-')
		sign_exp = (*((tod->cp)++) == '-');
	set_exp_limit(&exp_limit, tod, sign_exp);
	while (ft_isdigit(*(tod->cp)))
	{
		if (is_overflow(tod, exp_limit, sign_exp))
			return (IS_OVER_FLOW);
		tod->exponent = tod->exponent * 10 + (*((tod->cp)++) - '0');
	}
	tod->exponent *= (1 - 2 * sign_exp);
	return (NOT_OVER_FLOW);
}

void	normalize_exponent(t_strtod *tod)
{
	intmax_t	incr;

	if (tod->exponent < 0)
	{
		incr = -(intmax_t)tod->int_no;
		if (incr < tod->exponent)
			incr = tod->exponent;
	}
	else
	{
		incr = (intmax_t)tod->dig_no - (intmax_t)tod->int_no;
		if (tod->exponent < incr)
			incr = tod->exponent;
	}
	tod->int_no += incr;
	tod->exponent -= incr;
}

double	ft_strtod(const char *nptr, char **endptr)
{
	t_strtod	tod;

	ft_bzero(&tod, sizeof(t_strtod));
	tod.cp = nptr;
	skip_sp_set_negative(&tod);
	if (is_inf(&tod) || is_nan(&tod))
		return (set_endptr(&tod, endptr));
	set_base(&tod);
	tod.start_of_digits = tod.cp;
	scan_digits(&tod);
	if (parse_exp(&tod))
		return (set_endptr(&tod, endptr));
	normalize_exponent(&tod);
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
	// printf("%f\n", tmp);
	// printf("%s\n", ar);
}
