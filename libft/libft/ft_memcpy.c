/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:11:27 by vame              #+#    #+#             */
/*   Updated: 2014/12/05 12:52:20 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*dst_tmp;

	tmp = (unsigned char *)src;
	dst_tmp = (unsigned char *)dst;
	while (n--)
		*dst_tmp++ = *tmp++;
	return ((void *)dst);
}
