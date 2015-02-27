/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:57:17 by vame              #+#    #+#             */
/*   Updated: 2015/01/14 16:12:30 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long long int n)
{
	size_t	len;

	len = 1;
	while (n > 9 || n < -9)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char			*ft_itoa(long long int n)
{
	size_t	len;
	size_t	sign;
	char	*dst;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_len(n) + sign;
	if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	dst[len--] = '\0';
	while (n > 9 || n < -9)
	{
		dst[len--] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	dst[len--] = ft_abs(n) + '0';
	if (sign == 1)
		dst[len] = '-';
	return (dst);
}
