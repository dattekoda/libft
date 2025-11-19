/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_str_to_mpn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 06:55:05 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 07:29:40 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod_define.h"
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
	size_t		i;

	i = 0;
	carry = limb;
	while (carry && i < mpn->size)
	{
		mpn->limbs[i] += carry;
		carry = 0;
		if (mpn->limbs[i++] < carry)
			carry = 1;
	}
	if (carry && mpn->size < MPNSIZE_MAX)
		mpn->limbs[mpn->size++] = carry;
	else if (carry)
		return (IS_OVER_FLOW);
	return (NOT_OVER_FLOW);
}

// calc 2^n
int	_mpn_mul_power_2(t_mpn *mpn, unsigned char n)
{
	mp_limb_t	carry;
	mp_limb_t	new_carry;
	size_t		i;

	carry = 0;
	i = 0;
	while (i < mpn->size)
	{
		new_carry = mpn->limbs[i] >> (64 - n);
		mpn->limbs[i] = (mpn->limbs[i] << n) | carry;
		carry = new_carry;
		i++;
	}
	if (carry && new_carry)
		mpn->limbs[mpn->size++] = carry;
	else if (carry)
		return (IS_OVER_FLOW);
	return (NOT_OVER_FLOW);
}

int	_mpn_mul_10(t_mpn *mpn, mp_limb_t limb)
{
	t_mpn		tmp;
	mp_limb_t	carry;
	size_t		i;
	__uint128_t	sum;

	ft_memmove(&tmp, mpn, sizeof(t_mpn));
	if (_mpn_mul_power_2(mpn, 3) || _mpn_mul_power_2(&tmp, 1))
		return (IS_OVER_FLOW);
	carry = 0;
	i = 0;
	while (i < tmp.size || carry)
	{
		if (MPNSIZE_MAX <= i)
			return (IS_OVER_FLOW);
		sum = carry;
		if (i < mpn->size)
			sum += mpn->limbs[i];
		if (i < tmp.size)
			sum += tmp.limbs[i];
		mpn->limbs[i] = sum & UINT64_MAX;
		carry = sum >> 64;
		if (mpn->size <= i && (mpn->limbs[i] || carry))
			mpn->size = i + 1;
		i++;
	}
	return (NOT_OVER_FLOW);
}
