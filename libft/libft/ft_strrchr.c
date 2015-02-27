/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:54:33 by vame              #+#    #+#             */
/*   Updated: 2015/02/06 10:36:45 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len_s;
	char	chr;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	chr = c;
	while (*s != '\0')
		s++;
	if (chr == '\0')
		return ((char *)s);
	s--;
	while (i < len_s)
	{
		if (*s == chr)
			return ((char *)s);
		i++, s--;
	}
	return (NULL);
}
