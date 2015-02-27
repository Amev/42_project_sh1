/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:40:51 by vame              #+#    #+#             */
/*   Updated: 2014/11/20 10:27:50 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;
	unsigned char	*dst_tmp;

	tmp = (unsigned char *)src;
	dst_tmp = (unsigned char *)dst;
	if (tmp > dst_tmp)
		return (ft_memcpy(dst, src, len));
	while (len--)
		dst_tmp[len] = (unsigned char)tmp[len];
	return ((void *)dst_tmp);
}
