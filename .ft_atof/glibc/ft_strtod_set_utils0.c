/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_set_utils0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:09:05 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 17:47:57 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "libft.h"
#include <stdbool.h>


static bool	count_zeros(t_strtod *tod);

void	skip_sp_set_negative(t_strtod *tod)
{
	while (ft_isspace(*(tod->cp)))
		tod->cp++;
	if (*(tod->cp) == '-' || *(tod->cp) == '+')
		tod->negative = (*((tod->cp)++) == '-');
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

static bool	count_zeros(t_strtod *tod)
{
	bool	already_point;

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
	tod->start_of_digits = tod->cp;
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
