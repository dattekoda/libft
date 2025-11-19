/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_set_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:13:06 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/19 18:30:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "libft.h"
#include <stdbool.h>

static void	set_exp_limit(intmax_t *exp_limit, t_strtod *tod, bool sign_exp)
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

static int	is_overflow(t_strtod *tod, intmax_t exp_limit, bool sign_exp)
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
