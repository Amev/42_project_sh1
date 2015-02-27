/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 10:54:44 by vame              #+#    #+#             */
/*   Updated: 2015/01/22 13:34:36 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags		*ptf_flags_init(t_flags **flags)
{
	t_flags		*new;

	if (!(new = (t_flags *)malloc(sizeof(*new))))
		return (NULL);
	new->htg = 0;
	new->plus = 0;
	new->minus = 0;
	new->zero = 0;
	new->space = 0;
	new->l = 0;
	new->ll = 0;
	new->h = 0;
	new->hh = 0;
	new->j = 0;
	new->z = 0;
	new->field = 0;
	new->precision = -1;
	*flags = new;
	return (*flags);
}

void		ptf_put_easy_flags(char flag, t_flags **flags)
{
	if (flag == '#')
		(*flags)->htg = 1;
	else if (flag == '0')
		(*flags)->zero = 1;
	else if (flag == '+')
		(*flags)->plus = 1;
	else if (flag == '-')
		(*flags)->minus = 1;
	else if (flag == ' ')
		(*flags)->space = 1;
	else if (flag == 'j')
		(*flags)->j = 1;
	else if (flag == 'z')
		(*flags)->z = 1;
}

int			ptf_put_int_flags(char *f, int *i, t_flags **flags)
{
	int			j;
	int			nb;
	char		*tmp;
	int			select;

	select = 0;
	if (!(nb = 0) && (f[(*i)] == '.' || (f[(*i)] > '0' && f[(*i)] <= '9')))
	{
		if (!(j = 0) && f[(*i)] == '.' && (*i += 1) >= 0)
			select = 1;
		while (f[(*i) + j] >= '0' && f[(*i) + j] <= '9')
			j++;
		if (!(tmp = ft_strnew(j)))
			return (0);
		j = 0;
		while (f[(*i)] >= '0' && f[(*i)] <= '9')
			tmp[j++] = f[(*i)++];
		nb = ft_atoi(tmp);
		free(tmp);
		if ((*i -= 1) >= 0 && select == 0)
			(*flags)->field = nb;
		else
			(*flags)->precision = nb;
	}
	return (1);
}

int			ptf_put_flags(char *f_str, t_flags **flags, va_list arg)
{
	int			i;

	i = 0;
	while (f_str[i])
	{
		if (f_str[i] == '*')
			ptf_asterisk(arg, flags, 0);
		else if (f_str[i] == '.' && f_str[i + 1] == '*' && ++i)
			ptf_asterisk(arg, flags, 1);
		ptf_put_easy_flags(f_str[i], flags);
		if (!(ptf_put_int_flags(f_str, &i, flags)))
			return (0);
		if (f_str[i] == 'l' && f_str[i + 1] != 'l')
			(*flags)->l = 1;
		else if (f_str[i] == 'h' && f_str[i + 1] != 'h')
			(*flags)->h = 1;
		else if (f_str[i] == 'l' && f_str[i + 1] == 'l' && ++i)
			(*flags)->ll = 1;
		else if (f_str[i] == 'h' && f_str[i + 1] == 'h' && ++i)
			(*flags)->hh = 1;
		i++;
	}
	return (1);
}

t_flags		*ptf_check_flags(t_flags **flags, const char **f, va_list arg)
{
	int			i;
	int			j;
	char		*f_str;

	i = 0;
	while (ptf_is_conversion((*f)[i]) == 0 && ptf_is_flag((*f)[i]) == 1)
		i++;
	f_str = ft_strnew(i);
	*flags = ptf_flags_init(flags);
	if (!(f_str && *flags))
		return (NULL);
	j = 0;
	while (j++ < i)
		f_str[j - 1] = (*f)[j - 1];
	if (!(ptf_put_flags(f_str, flags, arg)))
		return (NULL);
	free(f_str);
	*f += i;
	return (*flags);
}
