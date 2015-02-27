/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:07:36 by vame              #+#    #+#             */
/*   Updated: 2015/02/02 14:47:28 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		len;
	char		*dst;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(dst = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while (s1 && *s1)
		dst[i++] = *s1++;
	while (s2 && *s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
