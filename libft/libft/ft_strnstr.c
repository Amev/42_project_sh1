/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:05:11 by vame              #+#    #+#             */
/*   Updated: 2014/11/22 13:59:05 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		len;

	if (!s1)
		return (NULL);
	if (!s2 || *s2 == '\0')
		return ((char *)s1);
	i = 0;
	len = ft_strlen(s2);
	while (*s1 && i + len <= n)
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char *)s1);
		i++;
		s1++;
	}
	return (NULL);
}
