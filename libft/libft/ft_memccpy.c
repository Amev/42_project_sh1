/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:19:24 by vame              #+#    #+#             */
/*   Updated: 2014/11/13 14:55:43 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*dst_tmp;

	tmp = (unsigned char *)src;
	dst_tmp = (unsigned char *)dst;
	while (n--)
	{
		if (*tmp == (unsigned char)c)
		{
			*dst_tmp++ = *tmp++;
			return ((void *)dst_tmp);
		}
		*dst_tmp++ = *tmp++;
	}
	return (NULL);
}
