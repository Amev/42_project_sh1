/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_print_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 11:12:21 by vame              #+#    #+#             */
/*   Updated: 2015/01/21 11:45:16 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ptf_htg_preci(char *res, char tag, t_flags **f)
{
	size_t		len;

	if ((tag == 'o' || tag == 'O') && (*f)->htg == 1)
	{
		len = ft_strlen(res);
		if ((*f)->precision < 1 && len == 1 && res[0] == '0')
			(*f)->precision = 1;
		else if ((int)len >= (*f)->precision)
			(*f)->precision = (int)len + 1;
		(*f)->htg = 0;
	}
}

wchar_t		*ptf_wstr_preci(wchar_t *str, t_flags **flags, int *len)
{
	int			i;
	int			j;
	wchar_t		*dst;

	i = 0;
	while (str[i])
		i++;
	if (!(dst = (wchar_t *)malloc(sizeof(wchar_t) * (i + 1))))
		return (NULL);
	j = 0;
	while (j++ < i)
		dst[j - 1] = str[j - 1];
	dst[j - 1] = 0;
	i--;
	while (*len > (*flags)->precision && (*flags)->precision != -1)
	{
		*len -= ft_wcharlen(dst[i]);
		dst[i--] = 0;
	}
	return (dst);
}

char		*ptf_strncpy(char *dst, char *src, size_t n)
{
	size_t		len;
	size_t		i;

	i = 0;
	len = ft_strlen(src);
	while (i < len)
	{
		if (src[n])
			dst[i++] = src[n++];
		else
			dst[i++] = '\0';
	}
	return (dst);
}

char		*ptf_print_sign(char **nb)
{
	char		*tmp;
	size_t		len;
	size_t		i;

	i = 0;
	if (*nb[i] == '+' || *nb[i] == '-' || *nb[i] == ' ')
	{
		len = ft_strlen(*nb);
		ft_putchar((*nb)[i++]);
		if (!(tmp = ft_strnew(len - 1)))
			return (NULL);
		while (i < len)
		{
			tmp[i - 1] = (*nb)[i];
			i++;
		}
		free(*nb);
		return (tmp);
	}
	return (*nb);
}

char		*ptf_print_0x(char **str, char tag, t_flags **flags)
{
	char		*tmp;
	size_t		len;
	size_t		i;
	int			j;

	j = 0;
	while ((*str)[j] && j != -1)
		if ((*str)[j++] != '0')
			j = -1;
	if (((tag == 'p' || ((tag == 'X' || tag == 'x' || tag == 'o' || tag == 'O')
				&& ((*flags)->htg == 1 && j == -1))) && ((*flags)->zero == 1 &&
				(*flags)->precision == -1)) && (i = 1))
	{
		len = ft_strlen(*str);
		ft_putchar('0');
		if (!(j = 0) && tag != 'o' && tag != 'O' && ++i > 0)
			ft_putchar(tag == 'p' || tag == 'x' ? 'x' : 'X');
		if (!(tmp = ft_strnew(len - 1)))
			return (NULL);
		while (i < len)
			tmp[j++] = (*str)[i++];
		free(*str);
		return (tmp);
	}
	return (*str);
}
