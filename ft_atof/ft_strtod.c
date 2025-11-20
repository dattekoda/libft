/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:33:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/20 17:29:57 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_strtod_define.h"
#include "ft_strtod_utils.h"
#include "ft_strtod_set_utils.h"
#include <stddef.h>
#include <stdbool.h>
#include <endian.h> // big endian or little

#include <stdio.h>

int	set_tod(t_strtod *tod, const char *nptr)
{
	ft_bzero(tod, sizeof(t_strtod));
	tod->cp = nptr;
	skip_sp_set_negative(tod);
	if (is_inf(tod) || is_nan(tod))
		return (IS_OVER_FLOW);
	set_base(tod);
	tod->start_of_digits = tod->cp;
	scan_digits(tod);
	if (parse_exp(tod))
		return (IS_OVER_FLOW);
	normalize_exponent(tod);
	return (NOT_OVER_FLOW);
}

double	ft_strtod(const char *nptr, char **endptr)
{
	t_strtod	tod;

	if (set_tod(&tod, nptr))
		return (set_endptr(&tod, endptr));
	if (str_to_mpn(&tod))
		return (set_endptr(&tod, endptr));
	printf("%zu\n", tod.num.limbs[0]);
	return (set_endptr(&tod, endptr));
}

void	print_mpn(t_mpn *mpn)
{
	mp_size_t	i = num->size;

	printf("size: %ld\n", num->size);
	while (0 < i) {
		printf("%lu", num->limbs[--i]);
	}
}

int	main(int argc, char *argv[])
{
	double	tmp;
	char	*ar;

	if (argc == 1)
		return 1;
	tmp = ft_strtod(argv[1], &ar);
	printf("%f\n", tmp);
	// printf("%s\n", ar);
}
