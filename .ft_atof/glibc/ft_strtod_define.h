/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:41:50 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/19 19:17:30 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOD_DEFINE_H
# define FT_STRTOD_DEFINE_H

# include <stddef.h>
# include <stdint.h>

# define FLT_MIN_EXP	-1021
# define FLT_MANT_DIG	53
# define MIN_EXP		-1021
# define MAX_EXP		1024
# define MANT_DIG		FLT_MANT_DIG
# define MIN_10_EXP		-307
# define MAX_10_EXP		308

// # define howmany(x,y)	(((x)+((y)-1))/(y))
// (howmany (1 + ((MANT_DIG - (MIN_EXP) + 2) * 10) / 3, BITS_PER_MP_LIMB) + 2)

// # define MPN_VAR(name) mp_limb_t name[MPNSIZE_MAX]; mp_size_t name ## size
// # define PASTE(a,b) a ## b

# define BITS_PER_MP_LIMB 64

# define MPNSIZE_MAX	56 // 3590 / 64
# define MAX_DIG_PER_LIMB	19
# define MAX_FAC_PER_LIMB	10000000000000000000UL

# define BASE_SYMBOL_SIZE 17

# define IS_OVER_FLOW 1
# define NOT_OVER_FLOW 0

typedef uint64_t	mp_limb_t;
typedef int64_t		mp_size_t;
typedef int64_t		intmax_t;

# define RETURN_LIMB_SIZE	1 //howmany (MANT_DIG, BITS_PER_MP_LIMB)

typedef struct s_mpn
{
	mp_limb_t	limbs[MPNSIZE_MAX];
	mp_size_t	size;
}	t_mpn;

typedef struct s_strtod
{
	double		ret;
	int			negative;
	t_mpn		num;
	intmax_t	exponent;
	int			base;
	t_mpn		den;
	mp_limb_t	retval[RETURN_LIMB_SIZE];
	int			bits;
	const char	*cp;
	const char	*start_of_digits;
	size_t		dig_no;
	size_t		int_no;
	size_t		lead_zero;
}	t_strtod;

#endif