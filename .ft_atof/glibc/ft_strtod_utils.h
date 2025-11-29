/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:05:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 13:46:47 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOD_UTILS_H
# define FT_STRTOD_UTILS_H

# include "ft_strtod_define.h"
# include <stdbool.h>

// utils_set
int		parse_exp(t_strtod *tod);
void	normalize_exponent(t_strtod *tod);

// 0
int		is_hexalpha(int c);
int		tod_is_valid_num(t_strtod *tod);
double	set_endptr(t_strtod *tod, char **endptr);

// 1
double	ft_infinity(void);
double	ft_nan(void);
bool	is_inf(t_strtod *tod);
bool	is_nan(t_strtod *tod);

int	str_to_mpn(t_strtod *tod);

#endif