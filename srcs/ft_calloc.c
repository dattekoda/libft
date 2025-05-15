/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-26 07:50:50 by khanadat          #+#    #+#             */
/*   Updated: 2025-04-26 07:50:50 by khanadat         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total;
	unsigned char	*res;

	if (size > nmemb / SIZE_MAX)
		return (NULL);
	total = size * nmemb;
	if (total == 0)
		total = 1;
	res = malloc(total);
	if (!res)
		return (NULL);
	ft_bzero(res, total);
	return (res);
}
