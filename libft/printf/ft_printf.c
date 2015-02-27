/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 10:23:56 by vame              #+#    #+#             */
/*   Updated: 2015/01/23 11:19:00 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ptf_int(char tag, va_list arg, t_flags **f)
{
	size_t			len;
	char			*nb;
	char			*tmp;

	nb = ptf_conv_nb(arg, tag, f);
	len = ft_strlen(nb);
	if (((*f)->plus == 1 || (*f)->space == 1) && nb[0] != '-')
	{
		if (!(tmp = ft_strjoin((*f)->plus == 1 ? "+" : " ", nb)))
			return (-1);
		free(nb);
		nb = tmp;
		len++;
	}
	if ((*f)->zero == 1 && (*f)->precision == -1 && !(nb = ptf_print_sign(&nb)))
		return (-1);
	if ((*f)->minus == 1)
		ft_putstr(nb);
	(*f)->field -= len;
	while ((*f)->field-- > 0 && ++len > 0)
		ft_putchar((*f)->zero == 1 && (*f)->minus == 0 ? '0' : ' ');
	if ((*f)->minus == 0)
		ft_putstr(nb);
	free(nb);
	return (len);
}

int		ptf_str(char *str, t_flags **flags, char tag)
{
	size_t			len;

	if (tag == 's' && str == NULL)
		str = ft_strdup("(null)");
	else if (tag == 's')
		str = ft_strdup(str);
	len = ft_strlen(str);
	while (tag == 's' && (*flags)->precision != -1 && len >
			(size_t)(*flags)->precision)
		str[len-- - 1] = '\0';
	if (!(str = ptf_print_0x(&str, tag, flags)))
		return (-1);
	if ((*flags)->minus == 1)
		ft_putstr(str);
	(*flags)->field -= (int)len;
	while ((*flags)->field > 0)
	{
		ft_putchar((*flags)->zero == 1 && (*flags)->minus == 0 ? '0' : ' ');
		(*flags)->field--;
		len++;
	}
	if ((*flags)->minus == 0)
		ft_putstr(str);
	free(str);
	return (len);
}

int		ptf_nb_with_base(char tag, va_list arg, t_flags **flags)
{
	char			*result;
	char			*tmp;
	size_t			len;
	unsigned int	base;
	int				i;

	i = 0;
	base = ptf_choose_base(tag);
	if (!(result = ptf_cnv(base, arg, tag, flags)))
		return (-1);
	while (result[i] && i != -1)
		if (result[i++] != '0')
			i = -1;
	if (((tag == 'X' || tag == 'x' || tag == 'o' || tag == 'O') &&
				(*flags)->htg == 1 && i == -1) || tag == 'p')
	{
		if (!(tmp = ft_strjoin(tag == 'o' || tag == 'O' ? "0" : "0x", result)))
			return (-1);
		free(result);
		result = tmp;
	}
	if (tag == 'X')
		result = ptf_toupper(&result);
	len = ptf_str(result, flags, tag);
	return (len);
}

int		ptf_check_tag(char tag, va_list arg, t_flags **flags)
{
	if (!tag)
		return (0);
	else if (tag == 'C' || (tag == 'c' && (*flags)->l == 1))
		return (ptf_print_wchar(va_arg(arg, wint_t), flags));
	else if (tag == 'S' || (tag == 's' && (*flags)->l == 1))
		return (ptf_print_wstr(va_arg(arg, wchar_t *), flags));
	else if (tag == 'c')
		return (ptf_no_conversion(va_arg(arg, int), flags));
	else if (tag == 'o' || tag == 'b' || tag == 'x' || tag == 'X' || tag == 'u'
			|| tag == 'p' || tag == 'O' || tag == 'U')
		return (ptf_nb_with_base(tag, arg, flags));
	else if (tag == 'd' || tag == 'D' || tag == 'i')
		return (ptf_int(tag, arg, flags));
	else if (tag == 's')
		return (ptf_str(va_arg(arg, char *), flags, tag));
	else
		return (ptf_no_conversion(tag, flags));
}

int		ft_printf(const char *format, ...)
{
	va_list			arg;
	t_flags			*flags;
	int				rturn;
	int				tmp;

	va_start(arg, format);
	rturn = 0;
	while (*format && ptf_put_color(&format) == 1)
	{
		if (*format == '%' && format++)
		{
			if (!(flags = ptf_check_flags(&flags, &format, arg)))
				return (-1);
			if ((tmp = ptf_check_tag(*format, arg, &flags)) == -1)
				return (-1);
			rturn += tmp;
			free(flags);
		}
		else if (rturn++ >= 0)
			ft_putchar(*format);
		if (*format)
			format++;
	}
	va_end(arg);
	return (rturn);
}
