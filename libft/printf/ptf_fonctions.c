/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 12:50:42 by vame              #+#    #+#             */
/*   Updated: 2015/01/22 10:27:23 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ptf_toupper(char **str)
{
	int			i;

	i = 0;
	while ((*str) && (*str)[i++])
		(*str)[i - 1] = ft_toupper((*str)[i - 1]);
	return (*str);
}

unsigned int	ptf_choose_base(char tag)
{
	if (tag == 'b')
		return (2);
	else if (tag == 'o' || tag == 'O')
		return (8);
	else if (tag == 'u' || tag == 'U')
		return (10);
	else
		return (16);
}

int				ptf_is_conversion(char c)
{
	return (c == '%' || c == 'c' || c == 'C' || c == 's' || c == 'S' || c == 'd'
	|| c == 'D' || c == 'i' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
	c == 'o' || c == 'O' || c == 'b' ? 1 : 0);
}

int				ptf_is_flag(char c)
{
	return (c == '#' || (c >= '0' && c <= '9') || c == '+' || c == '-' || c ==
	' ' || c == 'l' || c == 'h' || c == 'j' || c == 'z' || c == '.' || c == '*'
	? 1 : 0);
}

char			*ptf_cnv(unsigned int base, va_list arg, char tag, t_flags **f)
{
	char		*res;

	if ((*f)->j == 1)
		res = ft_itoa_base_u(va_arg(arg, uintmax_t), base);
	else if ((*f)->ll == 1)
		res = ft_itoa_base_u(va_arg(arg, unsigned long long int), base);
	else if (tag == 'U' || tag == 'O' || tag == 'p' || (*f)->l == 1 ||
			(*f)->z == 1)
		res = ft_itoa_base_u(va_arg(arg, unsigned long int), base);
	else if ((*f)->h == 1)
		res = ft_itoa_base_u((unsigned short)va_arg(arg, unsigned int), base);
	else if ((*f)->hh == 1)
		res = ft_itoa_base_u((unsigned char)va_arg(arg, unsigned int), base);
	else
		res = ft_itoa_base_u(va_arg(arg, unsigned int), base);
	ptf_htg_preci(res, tag, f);
	if (res && (*f)->precision != -1)
	{
		(*f)->zero = 0;
		res = ptf_precision(res, f);
	}
	return (res);
}
