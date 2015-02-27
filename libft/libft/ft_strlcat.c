/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:50:03 by vame              #+#    #+#             */
/*   Updated: 2015/02/09 10:22:51 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size--)
	{
		while (*dst && size)
		{
			len++;
			dst++;
			size--;
		}
		if (size == 0 && *dst)
			len++;
	}
	while (*src && size > 0 && dst)
	{
		*dst++ = *src++;
		len++;
		size--;
		if (*src == '\0' || size == 0)
			*dst = '\0';
	}
	while (*src++)
		len++;
	return (len);
}
