/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 07:04:04 by khanadat          #+#    #+#             */
/*   Updated: 2025-05-28 07:04:04 by khanadat         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_realloc(void *ptr, size_t old_sz, size_t new_sz)
{
	void	*newp;

	if (new_sz == 0)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_sz));
	newp = malloc(new_sz);
	if (!newp)
		return (NULL);
	if (old_sz > new_sz)
		old_sz = new_sz;
	ft_memcpy(newp, ptr, old_sz);
	free(ptr);
	return (newp);
}
