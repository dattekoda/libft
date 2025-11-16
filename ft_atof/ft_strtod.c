/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:33:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/17 00:28:48 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

#ifndef NULL
# define NULL 0
#endif

static int	maxExponent = 511;

static double	powers0f10[] = {
	10.,
	100.,
	1.0e4,
	1.0e8,
	1.0e16,
	1.0e32,
	1.0e64,
	1.0e128,
	1.0e256
};

int	set_strtod(int fraction, char **endPtr, int sign, char *p)
{
	if (endPtr)
		*endPtr = (char *)p;
	if (sign)
		return (-fraction);
	return (fraction);
}

int	get_frac(int range, const char **p, int *mantSize)
{
	int				frac;
	register int	c;
	
	frac = 0;
	while (range < *mantSize)
	{
		c = *((*p)++);
		if (c == '.')
			c = *((*p)++);
		frac = 10 * frac + (c - '0');
		(*mantSize)--;
	}
	return (frac);
}

#if 1
double	ft_strtod(const char *string, char **endPtr)
{
	int	sign = FALSE, expSign = FALSE;
	double	fraction, dblExp, *d;
	const char	*p;
	register int	c;
	int	exp = 0;
	int	fracExp = 0;
/* 	Exponent that derives from the fractional
	part. Under normal circumstances, it is
	the negative of the number of digits in F.
	However, if I is very long, the last digits
	of I get dropped. In this case, fracExp is
	incremented one for each dropped digit. */
	int	mantSize;
	int	decPt;	// Number of mantissa digits BEFORE decimal point.
	const char	*pExp;

	p = string;
	while (ft_isspace(*p))
		p++;
	if (*p == '-' || *p == '+')
		sign = (*(p++) == '-');
	
	// count the number of digits in the mantissa
	// and also locate the decimal point.
	decPt = -1;
	mantSize = 0;
	while (1) {
		c = *p;
		if (!ft_isdigit(c)) {
			if (c != '.' || 0 <= decPt)
				break ;
			decPt = mantSize;
		}
		p++;
		mantSize++;
	}
	// fprintf(stderr, "decPt\t\t: %d\n", decPt);
	// fprintf(stderr, "mantSize\t: %d\n", mantSize);
	
	// Now stuck up the digits in the mantissa. Use two integers to
	// collect 9 digits each (this is faster than using floating point).
	// If the mantissa has more than 18 digits, ignore the extras, since
	// they can't affact the value anyway.
	
	pExp = p;
	p -= mantSize;
	if (decPt < 0)
		decPt = mantSize;
	else
		mantSize--;
	if (18 < mantSize) {
		fracExp = decPt - 18;
		mantSize = 18;
	}
	else
		fracExp = decPt - mantSize;
	if (mantSize == 0)
	{
		p = string;
		return (set_strtod(0.0, endPtr, sign, (char *)p));
	}
	else
	{
		fprintf(stderr, "p    : %s\n", p);
		fprintf(stderr, "mantS: %d\n", mantSize);
		int	frac1, frac2;
		frac1 = get_frac(9, &p, &mantSize); // if it has more than 9 mantSize
		frac2 = get_frac(0, &p, &mantSize);
		fraction = (1.0e9 * frac1) + frac2;
		fprintf(stderr, "frac1: %d\n", frac1);
		fprintf(stderr, "frac2: %d\n", frac2);
		fprintf(stderr, "frac : %f\n", fraction);
	}

	// skim off the exponent
	p = pExp;
	if ((*p == 'E') || (*p == 'e')) {
		p++;
		if (*p == '-' || *p == '+')
			expSign = ((*(p++)) == '-');
		while (ft_isdigit(*p))
			exp = exp * 10 + (*(p++) - '0');
	}
	if (expSign)
		exp = fracExp - exp;
	else
		exp = fracExp + exp;
	fprintf(stderr, "exp:%d\n", exp);
	// generate a loating-point number that represents the exponent.
	// Do this by processing the exponent one bit at a time to combine
	// many powers of 2 of 10. Then combine the exponent with the
	// fraction.

	if (exp < 0) {
		expSign = TRUE;
		exp = -exp;
	}
	else
		expSign = FALSE;
	if (maxExponent < exp)
		exp = maxExponent;
	dblExp = 1.0;
	for (d = powers0f10; exp != 0; exp >>= 1, d += 1)
	{
		if (exp & 01)
			dblExp *= *d;
	}
	fprintf(stderr, "dblExp:%f\n", dblExp);
	if (expSign)
		fraction /= dblExp;
	else
		fraction *= dblExp;
	if (endPtr)
		*endPtr = (char *)p;
	if (sign)
		return (-fraction);
	return (fraction);
}

#endif

#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	double	tmp;

	if (argc == 1)
		return 1;
	tmp = ft_strtod(argv[1], NULL);
	printf("ft\t: %f\n", tmp);
	tmp = strtod(argv[1], NULL);
	printf("real\t: %f\n", tmp);
	printf("argv\t: %s\n", argv[1]);
	return 0;
}
