/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:48:08 by vame              #+#    #+#             */
/*   Updated: 2015/02/02 13:09:19 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b, size_t c)
{
	size_t	min;

	min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return (min);
}

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_min;

	if (n == 0 || !(s1 || s2))
		return (0);
	if (!s1)
		return (-(*s2));
	if (!s2)
		return (*s1);
	len_s1 = ft_strlen(s1) + 1;
	len_s2 = ft_strlen(s2) + 1;
	len_min = ft_min(len_s1, len_s2, n);
	return (ft_memcmp(s1, s2, len_min));
}
