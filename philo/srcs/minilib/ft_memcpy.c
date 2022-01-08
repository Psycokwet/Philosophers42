/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 16:29:20 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	while (len > 0)
	{
		len--;
		((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	}
	return (dst);
}
