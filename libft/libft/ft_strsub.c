/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:52:03 by vame              #+#    #+#             */
/*   Updated: 2014/11/25 14:39:47 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*dst;
	size_t		i;

	i = 0;
	if (!(dst = (char *)malloc(sizeof(char) * (len + 1))) || s == NULL)
		return (NULL);
	while (start--)
		s++;
	while (i < len)
		dst[i++] = *s++;
	dst[i] = '\0';
	return (dst);
}
