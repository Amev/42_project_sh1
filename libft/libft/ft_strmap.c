/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:18:03 by vame              #+#    #+#             */
/*   Updated: 2014/11/12 14:01:01 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	size_t	len;
	size_t	i;

	i = 0;
	if (!(s && f))
		return (NULL);
	len = ft_strlen(s);
	if (!(dst = (char *)malloc(sizeof(*dst) * len + 1)))
		return (NULL);
	while (i < len)
		dst[i++] = f(*s++);
	dst[i] = '\0';
	return (dst);
}
