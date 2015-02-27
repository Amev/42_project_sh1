/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:18:03 by vame              #+#    #+#             */
/*   Updated: 2014/11/12 10:41:32 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	size_t			len;
	size_t			i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!(s && f))
		return (NULL);
	len = ft_strlen(s);
	if (!(dst = (char *)malloc(sizeof(*dst) * len + 1)))
		return (NULL);
	while (i < len)
	{
		dst[i++] = f(j, s[j]);
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
