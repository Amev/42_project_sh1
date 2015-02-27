/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 10:34:46 by vame              #+#    #+#             */
/*   Updated: 2015/01/21 11:27:04 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ptf_no_conversion(char c, t_flags **flags)
{
	int		rturn;

	rturn = 1;
	if ((*flags)->minus == 1)
		ft_putchar(c);
	while ((*flags)->field > 1)
	{
		ft_putchar((*flags)->zero == 1 && (*flags)->minus == 0 ? '0' : ' ');
		(*flags)->field--;
		rturn++;
	}
	if ((*flags)->minus == 0)
		ft_putchar(c);
	return (rturn);
}

int			ptf_print_wchar(wchar_t c, t_flags **flags)
{
	int		rturn;
	int		len;

	rturn = 0;
	if ((len = ft_wcharlen(c)) == -1)
		return (-1);
	if ((*flags)->minus == 1)
		rturn += ft_putwchar(c);
	(*flags)->field -= len;
	while ((*flags)->field > 0)
	{
		ft_putchar((*flags)->zero == 1 && (*flags)->minus == 0 ? '0' : ' ');
		(*flags)->field--;
		rturn++;
	}
	if ((*flags)->minus == 0)
		rturn += ft_putwchar(c);
	return (rturn);
}

int			ptf_print_wstr(wchar_t *str, t_flags **flags)
{
	int			rturn;
	int			len;
	int			tmp;

	tmp = 0;
	rturn = 0;
	if (str == NULL && (tmp = 1))
		return (ptf_str(NULL, flags, 's'));
	if ((len = ft_wstrlen(str)) == -1)
		return (-1);
	if (!(str = ptf_wstr_preci(str, flags, &len)))
		return (-1);
	if ((*flags)->minus == 1)
		rturn += ft_putwstr(str);
	(*flags)->field -= len;
	while ((*flags)->field > 0)
	{
		ft_putchar((*flags)->zero == 1 && (*flags)->minus == 0 ? '0' : ' ');
		(*flags)->field--;
		rturn++;
	}
	if ((*flags)->minus == 0)
		rturn += ft_putwstr(str);
	free(str);
	return (rturn);
}

char		*ptf_precision(char *res, t_flags **f)
{
	char		*tmp;
	size_t		len;
	size_t		i;
	int			sign;

	sign = 0;
	if (res[0] == '-' && (sign = 1))
		res = ptf_strncpy(res, res, 1);
	len = ft_strlen(res);
	i = len >= (size_t)(*f)->precision ? 0 : (size_t)(*f)->precision - len;
	if (i + sign)
	{
		if (!(tmp = ft_strnew((*f)->precision + sign)))
			return (NULL);
		if (!(len = 0) && sign > 0)
			tmp[len++] = '-';
		while (len < i + sign)
			tmp[len++] = '0';
		tmp = ft_strcat(tmp, res);
		free(res);
		res = tmp;
	}
	if ((*f)->precision == 0 && res[0] == '0')
		res[0] = '\0';
	return (res);
}

char		*ptf_conv_nb(va_list arg, char tag, t_flags **f)
{
	char		*res;

	if ((*f)->j == 1)
		res = ft_itoa(va_arg(arg, intmax_t));
	else if ((*f)->ll == 1)
		res = ft_itoa(va_arg(arg, long long int));
	else if ((*f)->l == 1 || tag == 'D' || (*f)->z == 1)
		res = ft_itoa(va_arg(arg, long int));
	else if ((*f)->h == 1)
		res = ft_itoa((short)va_arg(arg, int));
	else if ((*f)->hh == 1)
		res = ft_itoa((char)va_arg(arg, int));
	else
		res = ft_itoa(va_arg(arg, int));
	if (res && (*f)->precision != -1)
	{
		(*f)->zero = 0;
		res = ptf_precision(res, f);
	}
	return (res);
}
