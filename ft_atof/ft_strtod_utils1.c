/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:09:33 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/18 22:11:35 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_strtod_define.h"
#include <endian.h>
#include <stdbool.h>

double	ft_infinity(void)
{
	double			a;
	unsigned char	*a_ptr;

	a = 0;
	a_ptr = (unsigned char *)&a;
	if (__BYTE_ORDER == __BIG_ENDIAN)
	{
		a_ptr[0] = 0x7F;
		a_ptr[1] = 0xF0;
	}
	else
	{
		a_ptr[7] = 0x7F;
		a_ptr[6] = 0xF0;
	}
	return (a);
}

double	ft_nan(void)
{
	double			a;
	unsigned char	*a_ptr;

	a = 0;
	a_ptr = (unsigned char *)&a;
	if (__BYTE_ORDER == __BIG_ENDIAN)
	{
		a_ptr[0] = 0x7F;
		a_ptr[1] = 0xF8;
	}
	else
	{
		a_ptr[7] = 0x7F;
		a_ptr[6] = 0xF8;
	}
	return (a);
}

bool	is_inf(t_strtod *tod)
{
	static const char	*inf_pattern = "infinity";
	size_t				i;

	i = 0;
	while ((tod->cp)[i] && i < 3)
	{
		if (ft_tolower((tod->cp)[i]) != inf_pattern[i])
			break ;
		i++;
	}
	if (i != 3)
		return (false);
	while ((tod->cp)[i] && i < 8)
	{
		if (ft_tolower((tod->cp)[i]) != inf_pattern[i])
			break ;
		i++;
	}
	tod->ret = ft_infinity();
	tod->cp += 3;
	if (i == 8)
		tod->cp += 5;
	return (true);
}

bool	is_nan(t_strtod *tod)
{
	static const char	*nan_pattern = "nan";
	size_t				i;

	i = 0;
	while ((tod->cp)[i] && i < 3)
	{
		if (ft_tolower((tod->cp)[i]) != nan_pattern[i])
			return (false);
		i++;
	}
	tod->ret = ft_nan();
	tod->cp += 3;
	return (true);
}
