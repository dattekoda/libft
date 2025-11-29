/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_str_to_mpn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 06:55:05 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 17:40:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "libft.h"
#include <stdint.h>
#include <string.h>

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

int	_mpn_add_1(t_mpn *mpn, mp_limb_t limb)
{
	mp_limb_t	carry;
	mp_size_t	i;

	i = 0;
	carry = limb;
	while (carry && i < mpn->size)
	{
		mpn->limbs[i] += carry;
		if (mpn->limbs[i] < carry)
			carry = 1;
		else
			carry = 0;
		i++;
	}
	if (carry && MPNSIZE_MAX <= mpn->size)
		return (IS_OVER_FLOW);
	else if (carry)
		mpn->limbs[mpn->size++] = carry;
	return (NOT_OVER_FLOW);
}

// calc 2^n
int	_mpn_mul_power_2(t_mpn *mpn, unsigned char n)
{
	mp_limb_t	carry;
	mp_limb_t	new_carry;
	mp_size_t	i;

	if (n == 0)
		return (NOT_OVER_FLOW);
	if (64 <= n)
		return (IS_OVER_FLOW);
	carry = 0;
	i = 0;
	while (i < mpn->size)
	{
		new_carry = mpn->limbs[i] >> (64 - n);
		mpn->limbs[i] = (mpn->limbs[i] << n) | carry;
		carry = new_carry;
		i++;
	}
	if (carry && mpn->size < MPNSIZE_MAX)
		mpn->limbs[mpn->size++] = carry;
	else if (carry)
		return (IS_OVER_FLOW);
	return (NOT_OVER_FLOW);
}

int	_mpn_mul_10(t_mpn *mpn)
{
	__uint128_t	carry;
	mp_size_t	i;

	carry = 0;
	i = 0;
	while (i < mpn->size)
	{
		carry = (__uint128_t)mpn->limbs[i] * 5ULL + carry;
		mpn->limbs[i++] = carry & UINT64_MAX;
		carry >>= 64;
	}
	if (carry)
	{
		if (MPNSIZE_MAX <= mpn->size)
			return ((IS_OVER_FLOW));
		mpn->limbs[mpn->size++] = carry;
	}
	return (_mpn_mul_power_2(mpn, 1));
}

int	char_to_digit(char c, int base)
{
	if (base == 10)
	{
		if (ft_isdigit(c))
			return (c - '0');
	}
	else if (base == 16)
	{
		if (ft_isdigit(c))
			return (c - '0');
		if ('a' <= c && c <= 'f')
			return (10 + c - 'a');
		if ('A' <= c && c <= 'F')
			return (10 + c - 'A');
	}
	return (-1);
}

int	_mpn_mul_1(t_mpn *mpn, const mp_limb_t limb)
{
	mp_size_t	i;
	__uint128_t	carry;

	i = 0;
	carry = 0;
	while (i < mpn->size)
	{
		carry = (__uint128_t)mpn->limbs[i] * (__uint128_t)limb + carry;
		mpn->limbs[i++] = carry & UINT64_MAX;
		carry >>= 64;
	}
	if (carry)
	{
		if (MPNSIZE_MAX <= mpn->size)
			return (IS_OVER_FLOW);
		mpn->limbs[mpn->size++] = carry;
	}
	return (NOT_OVER_FLOW);
}

int	_mpn_add(t_mpn *mpn, t_mpn val)
{
	__uint128_t	carry;
	mp_size_t	i;

	carry = 0;
	i = 0;
	while (i < val.size || i < mpn->size)
	{
		if (i < val.size)
			carry += val.limbs[i];
		if (i < mpn->size)
			carry += mpn->limbs[i];
		mpn->limbs[i++] = carry & UINT64_MAX;
		carry >>= 64;
	}
	mpn->size = i;
	if (carry)
	{
		if (mpn->size == MPNSIZE_MAX)
			return (IS_OVER_FLOW);
		mpn->limbs[mpn->size++] = carry;
	}
	return (NOT_OVER_FLOW);
}

static int	internal_pmn_mul(t_mpn *mpn, t_mpn *res, t_mpn *val, mp_size_t i);

int	_mpn_mul(t_mpn *mpn, t_mpn val)
{
	t_mpn		res;
	mp_size_t	i;

	ft_bzero(&res, sizeof(t_mpn));
	if (mpn->size == 0 || val.size == 0)
		return ((mpn->size = 0, NOT_OVER_FLOW));
	i = 0;
	while (i < val.size)
	{
		if (internal_pmn_mul(mpn, &res, &val, i))
			return (IS_OVER_FLOW);
		i++;
	}
	*mpn = res;
	return (NOT_OVER_FLOW);
}

int	internal_pmn_mul(t_mpn *mpn, t_mpn *res, t_mpn *val, mp_size_t i)
{
	__uint128_t	carry;
	__uint128_t	product;
	mp_size_t	j;

	carry = 0;
	j = 0;
	while (j < mpn->size)
	{
		if (MPNSIZE_MAX <= i + j)
			return (IS_OVER_FLOW);
		product = (__uint128_t)mpn->limbs[i] \
		* (__uint128_t)val->limbs[j] + res->limbs[i + j] + carry;
		res->limbs[i + j++] = product & UINT64_MAX;
		carry = product >> 64;
	}
	if (carry)
	{
		if (MPNSIZE_MAX <= i + j)
			return (IS_OVER_FLOW);
		res->limbs[i + j] = (mp_limb_t)carry;
		if (res->size < i + j + 1)
			res->size = i + j + 1;
	}
	else if (res->size < i + j)
		res->size = i + j;
	return (NOT_OVER_FLOW);
}
