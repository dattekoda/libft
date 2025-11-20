/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_str_to_mpn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:00:00 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 11:41:04 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "libft.h"
#include <stdint.h>

/* 
 * _mpn_add_1: 多倍長数に1リムを加算
 * キャリーを処理しながら加算を行う
 */
void	_mpn_add_1(t_mpn *mpn, mp_limb_t limb)
{
	mp_limb_t	tmp;
	mp_limb_t	carry;
	mp_size_t	i;

	i = 0;
	carry = limb;
	while (carry && i < mpn->size)
	{
		mpn->limbs[i] += carry;
		// オーバーフローした場合、キャリーが発生
		carry = (mpn->limbs[i] < carry) ? 1 : 0;
		i++;
	}
	// 最上位リムでキャリーが発生した場合、新しいリムを追加
	if (carry && mpn->size < MPNSIZE_MAX)
	{
		mpn->limbs[mpn->size] = carry;
		mpn->size++;
	}
}

/*
 * _mpn_mul_10: 多倍長数を10倍する
 * 最適化版: 10 = 2 * 5 として計算
 */
int	_mpn_mul_10(t_mpn *mpn)
{
	__uint128_t	carry;
	mp_size_t	i;

	// まず5倍する
	carry = 0;
	for (i = 0; i < mpn->size; i++)
	{
		carry = mpn->limbs[i] * 5ULL + carry;
		mpn->limbs[i] = carry & UINT64_MAX;
		carry >>= 64;
	}
	if (carry)
	{
		if (mpn->size < MPNSIZE_MAX)
		{
			mpn->limbs[mpn->size++] = carry;
		}
		else
			return (IS_OVER_FLOW);
	}

	// 次に2倍する（左シフト1ビット）
	carry = 0;
	for (i = 0; i < mpn->size; i++)
	{
		mp_limb_t new_carry = mpn->limbs[i] >> 63;
		mpn->limbs[i] = (mpn->limbs[i] << 1) | carry;
		carry = new_carry;
	}
	if (carry)
	{
		if (mpn->size < MPNSIZE_MAX)
		{
			mpn->limbs[mpn->size++] = carry;
		}
		else
			return (IS_OVER_FLOW);
	}

	return (NOT_OVER_FLOW);
}

/*
 * 文字を数値に変換（10進数/16進数対応）
 */
static int	char_to_digit(char c, int base)
{
	if (base == 10)
	{
		if (c >= '0' && c <= '9')
			return (c - '0');
	}
	else if (base == 16)
	{
		if (c >= '0' && c <= '9')
			return (c - '0');
		if (c >= 'a' && c <= 'f')
			return (c - 'a' + 10);
		if (c >= 'A' && c <= 'F')
			return (c - 'A' + 10);
	}
	return (-1);
}

/*
 * str_to_mpn: 文字列を多倍長数に変換
 * 
 * @param mpn: 結果を格納する多倍長数構造体
 * @param str: 変換元の文字列（数字部分の開始位置）
 * @param len: 変換する文字数
 * @param base: 基数（10 or 16）
 * @return: オーバーフローが発生した場合IS_OVER_FLOW、それ以外はNOT_OVER_FLOW
 */
int	str_to_mpn(t_mpn *mpn, const char *str, size_t len, int base)
{
	size_t		i;
	int			digit;
	mp_limb_t	ten_in_limb[MAX_DIG_PER_LIMB + 1];
	size_t		digits_in_limb;
	mp_limb_t	accumulator;

	// 初期化
	ft_bzero(mpn, sizeof(t_mpn));
	if (len == 0)
		return (NOT_OVER_FLOW);

	if (base == 10)
	{
		// 10進数の場合は、MAX_DIG_PER_LIMB桁ごとにまとめて処理
		set_ten_in_limb(ten_in_limb);
		i = 0;
		
		while (i < len)
		{
			// 最大MAX_DIG_PER_LIMB桁をまとめて処理
			digits_in_limb = 0;
			accumulator = 0;
			
			while (i < len && digits_in_limb < MAX_DIG_PER_LIMB)
			{
				digit = char_to_digit(str[i], base);
				if (digit < 0)
				{
					// 小数点をスキップ
					if (str[i] == '.')
					{
						i++;
						continue;
					}
					break;
				}
				accumulator = accumulator * 10 + digit;
				digits_in_limb++;
				i++;
			}
			
			if (digits_in_limb > 0)
			{
				// mpn *= 10^digits_in_limb
				if (mpn->size > 0)
				{
					if (_mpn_mul_1(mpn, ten_in_limb[digits_in_limb]))
						return (IS_OVER_FLOW);
				}
				
				// mpn += accumulator
				if (accumulator > 0)
				{
					if (mpn->size == 0)
					{
						mpn->limbs[0] = accumulator;
						mpn->size = 1;
					}
					else
					{
						_mpn_add_1(mpn, accumulator);
					}
				}
			}
		}
	}
	else if (base == 16)
	{
		// 16進数の場合は、16桁（64ビット）ごとにまとめて処理
		i = 0;
		while (i < len)
		{
			digits_in_limb = 0;
			accumulator = 0;
			
			// 最大16桁（64ビット）をまとめて処理
			while (i < len && digits_in_limb < 16)
			{
				digit = char_to_digit(str[i], base);
				if (digit < 0)
				{
					// 小数点をスキップ
					if (str[i] == '.')
					{
						i++;
						continue;
					}
					break;
				}
				accumulator = (accumulator << 4) | digit;
				digits_in_limb++;
				i++;
			}
			
			if (digits_in_limb > 0)
			{
				// mpn *= 16^digits_in_limb
				if (mpn->size > 0)
				{
					mp_limb_t shift_amount = digits_in_limb * 4;
					mp_limb_t carry = 0;
					mp_size_t j;
					
					for (j = 0; j < mpn->size; j++)
					{
						__uint128_t shifted = (((__uint128_t)mpn->limbs[j]) << shift_amount) | carry;
						mpn->limbs[j] = shifted & UINT64_MAX;
						carry = shifted >> 64;
					}
					
					if (carry && mpn->size < MPNSIZE_MAX)
					{
						mpn->limbs[mpn->size++] = carry;
					}
					else if (carry)
						return (IS_OVER_FLOW);
				}
				
				// mpn += accumulator
				if (accumulator > 0)
				{
					if (mpn->size == 0)
					{
						mpn->limbs[0] = accumulator;
						mpn->size = 1;
					}
					else
					{
						_mpn_add_1(mpn, accumulator);
					}
				}
			}
		}
	}

	return (NOT_OVER_FLOW);
}

/*
 * _mpn_lshift: 多倍長数を左シフト（ビット単位）
 */
int	_mpn_lshift(t_mpn *mpn, size_t shift)
{
	mp_limb_t	carry;
	mp_size_t	i;

	if (shift == 0 || mpn->size == 0)
		return (NOT_OVER_FLOW);

	if (shift >= 64)
	{
		// リムブ単位のシフトが必要な場合
		size_t limb_shift = shift / 64;
		size_t bit_shift = shift % 64;
		
		// オーバーフローチェック
		if (mpn->size + (mp_size_t)limb_shift > MPNSIZE_MAX)
			return (IS_OVER_FLOW);
		
		// リムブを右から左へ移動
		for (i = mpn->size; i > 0; i--)
		{
			mpn->limbs[i + limb_shift - 1] = mpn->limbs[i - 1];
		}
		
		// 下位リムブをゼロで埋める
		for (i = 0; i < (mp_size_t)limb_shift; i++)
		{
			mpn->limbs[i] = 0;
		}
		
		mpn->size += limb_shift;
		
		// 追加のビットシフトが必要な場合
		if (bit_shift > 0)
			return (_mpn_lshift(mpn, bit_shift));
	}
	else
	{
		// 64ビット未満のシフト
		carry = 0;
		for (i = 0; i < mpn->size; i++)
		{
			mp_limb_t new_carry = mpn->limbs[i] >> (64 - shift);
			mpn->limbs[i] = (mpn->limbs[i] << shift) | carry;
			carry = new_carry;
		}
		
		if (carry)
		{
			if (mpn->size < MPNSIZE_MAX)
			{
				mpn->limbs[mpn->size++] = carry;
			}
			else
				return (IS_OVER_FLOW);
		}
	}

	return (NOT_OVER_FLOW);
}

/*
 * _mpn_rshift: 多倍長数を右シフト（ビット単位）
 */
void	_mpn_rshift(t_mpn *mpn, size_t shift)
{
	mp_limb_t	carry;
	mp_size_t	i;

	if (shift == 0 || mpn->size == 0)
		return;

	if (shift >= 64)
	{
		// リムブ単位のシフト
		size_t limb_shift = shift / 64;
		size_t bit_shift = shift % 64;
		
		if ((mp_size_t)limb_shift >= mpn->size)
		{
			// 全てのビットがシフトアウト
			mpn->size = 0;
			return;
		}
		
		// リムブを左から右へ移動
		for (i = 0; i < mpn->size - (mp_size_t)limb_shift; i++)
		{
			mpn->limbs[i] = mpn->limbs[i + limb_shift];
		}
		
		mpn->size -= limb_shift;
		
		// 追加のビットシフトが必要な場合
		if (bit_shift > 0)
			_mpn_rshift(mpn, bit_shift);
	}
	else
	{
		// 64ビット未満のシフト
		carry = 0;
		for (i = mpn->size; i > 0; i--)
		{
			mp_limb_t new_carry = mpn->limbs[i - 1] << (64 - shift);
			mpn->limbs[i - 1] = (mpn->limbs[i - 1] >> shift) | carry;
			carry = new_carry;
		}
		
		// 最上位リムブが0になった場合はサイズを調整
		while (mpn->size > 0 && mpn->limbs[mpn->size - 1] == 0)
			mpn->size--;
	}
}
