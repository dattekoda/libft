/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_set_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:15:35 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/19 18:31:41 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOD_SET_UTILS_H
# define FT_STRTOD_SET_UTILS_H

# include "ft_strtod_define.h"

// 0
void	skip_sp_set_negative(t_strtod *tod);
void	set_base(t_strtod *tod);
void	scan_digits(t_strtod *tod);

// 1
int		parse_exp(t_strtod *tod);
void	normalize_exponent(t_strtod *tod);

#endif