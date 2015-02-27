/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:05:11 by vame              #+#    #+#             */
/*   Updated: 2014/11/25 14:30:55 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;

	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1 != '\0')
	{
		i = 0;
		if (*s1 == s2[i])
		{
			while (s1[i] == s2[i] && s2[i] != '\0')
				i++;
			if (s2[i] == '\0')
				return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}