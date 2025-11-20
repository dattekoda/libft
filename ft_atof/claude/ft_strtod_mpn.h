/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_mpn.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:00:00 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 00:00:00 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOD_MPN_H
# define FT_STRTOD_MPN_H

# include "ft_strtod_define.h"

/* 基本的な多倍長数演算 */
int		_mpn_mul_1(t_mpn *mpn, mp_limb_t limb);
void	_mpn_add_1(t_mpn *mpn, mp_limb_t limb);
int		_mpn_mul_10(t_mpn *mpn);

/* シフト演算 */
int		_mpn_lshift(t_mpn *mpn, size_t shift);
void	_mpn_rshift(t_mpn *mpn, size_t shift);

/* 文字列から多倍長数への変換 */
int		str_to_mpn(t_mpn *mpn, const char *str, size_t len, int base);

/* より高度な演算（今後の実装用） */
int		_mpn_add(t_mpn *result, const t_mpn *a, const t_mpn *b);
int		_mpn_sub(t_mpn *result, const t_mpn *a, const t_mpn *b);
int		_mpn_mul(t_mpn *result, const t_mpn *a, const t_mpn *b);
int		_mpn_div(t_mpn *quotient, t_mpn *remainder, 
				const t_mpn *dividend, const t_mpn *divisor);

/* ユーティリティ関数 */
void	set_ten_in_limb(mp_limb_t *ten_in_limb);
void	mpn_copy(t_mpn *dest, const t_mpn *src);
int		mpn_compare(const t_mpn *a, const t_mpn *b);
int		mpn_is_zero(const t_mpn *mpn);
void	mpn_normalize(t_mpn *mpn);
int		mpn_count_leading_zeros(mp_limb_t limb);

/* デバッグ用関数 */
void	print_mpn(t_mpn *mpn);
void	test_str_to_mpn(const char *str, int base);

#endif
