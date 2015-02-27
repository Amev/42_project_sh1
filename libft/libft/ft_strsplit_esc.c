/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_esc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:45:42 by vame              #+#    #+#             */
/*   Updated: 2015/02/04 14:21:54 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strnb(char *s, char c, size_t *str_nb)
{
	size_t		i;

	i = 0;
	*str_nb = 0;
	while (*s && *s == c)
		s++;
	if (*s && (*s != 92 || *s + 1 != '\0'))
		*str_nb += 1;
	while (s[i] != '\0')
	{
		if (s[i] == 92 && s[i + 1] == c)
			i += 2;
		if (s[i++] == c && s[i] != c && s[i] != '\0')
			*str_nb += 1;
	}
	return (s);
}

static char		**ft_create_dst(char const *s, char c)
{
	size_t		str_nb;
	char		**dst;

	if (!(s && c))
		return (NULL);
	s = ft_strnb((char *)s, c, &str_nb);
	if (!(dst = (char **)malloc(sizeof(*dst) * (str_nb + 1))))
		return (NULL);
	dst[str_nb] = '\0';
	return (dst);
}

static char		*ft_cpy_s(char const *s, char c, size_t *len, size_t i)
{
	char		*dst;
	size_t		k;

	k = 1;
	if (s[i] != c && s[i + 1] == '\0')
		i++;
	if (!(dst = ft_strnew(*len)))
		return (NULL);
	while (*len)
	{
		if (s[i - k] == 92 && s[i - k + 1] == c)
			k++;
		dst[*len - 1] = s[i - k++];
		*len -= 1;
	}
	return (dst);
}

char			**ft_strsplit_esc(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		len;
	char		**dst;
	int			test;

	i = 0;
	j = 0;
	len = 0;
	if (!(dst = ft_create_dst(s, c)))
		return (NULL);
	while (s[i] && !(test = 0))
	{
		if (s[i] != c || (s[i] == 92 && s[i + 1] == c))
			if (++len && (s[i] == 92 && s[i + 1] == c && (test = 1)))
				i += 2;
		if (len && (s[i] == c || s[i + 1] == '\0'))
			if (!(dst[j++] = ft_cpy_s(s, c, &len, i)))
				return (NULL);
		if (!test)
			i++;
	}
	return (dst);
}
