/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:16:56 by vame              #+#    #+#             */
/*   Updated: 2014/11/12 11:33:27 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		len;
	char		*dst;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (*s == ' ' || *s == ',' || *s == '\n' || *s == '\t')
		s++;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == ',' ||
					s[len - 1] == '\n' || s[len - 1] == '\t'))
		len--;
	if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
		dst[i++] = *s++;
	dst[i] = '\0';
	return (dst);
}
