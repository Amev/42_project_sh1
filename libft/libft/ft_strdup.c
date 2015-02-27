/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:19:00 by vame              #+#    #+#             */
/*   Updated: 2015/01/15 15:47:27 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(s1);
	if (!(dst = (char *)malloc(sizeof(*dst) * len)))
		return (NULL);
	i = 0;
	while (s1 && *s1)
		dst[i++] = *s1++;
	dst[i] = '\0';
	return (dst);
}
