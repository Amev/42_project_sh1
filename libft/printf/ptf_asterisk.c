/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_asterisk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 10:52:09 by vame              #+#    #+#             */
/*   Updated: 2015/01/22 13:33:47 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ptf_asterisk(va_list arg, t_flags **flags, int i)
{
	long int		nb;

	nb = va_arg(arg, int);
	if (!i)
	{
		if (nb < 0 && (nb = -nb) >= 0)
			(*flags)->minus = 1;
		(*flags)->field = nb;
	}
	else
	{
		if (nb < 0)
			(*flags)->precision = -1;
		else
			(*flags)->precision = nb;
	}
}

int			ptf_search_color(const char *str)
{
	if (str[0] != '{' || str[4] != '}')
		return (-1);
	str++;
	if (ft_strncmp(str, "blk", 3) == 0)
		return (0);
	else if (ft_strncmp(str, "red", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "grn", 3) == 0)
		return (2);
	else if (ft_strncmp(str, "ylw", 3) == 0)
		return (3);
	else if (ft_strncmp(str, "blu", 3) == 0)
		return (4);
	else if (ft_strncmp(str, "mga", 3) == 0)
		return (5);
	else if (ft_strncmp(str, "cyn", 3) == 0)
		return (6);
	else if (ft_strncmp(str, "wht", 3) == 0)
		return (7);
	else if (ft_strncmp(str, "eoc", 3) == 0)
		return (8);
	else
		return (-1);
}

void		ptf_print_color(int color)
{
	if (color == 0)
		ft_putstr("\x1b[90m");
	else if (color == 1)
		ft_putstr("\x1b[91m");
	else if (color == 2)
		ft_putstr("\x1b[92m");
	else if (color == 3)
		ft_putstr("\x1b[93m");
	else if (color == 4)
		ft_putstr("\x1b[94m");
	else if (color == 5)
		ft_putstr("\x1b[95m");
	else if (color == 6)
		ft_putstr("\x1b[96m");
	else if (color == 7)
		ft_putstr("\x1b[97m");
	else if (color == 8)
		ft_putstr("\x1b[0m");
}

int			ptf_put_color(const char **format)
{
	int				color;
	int				i;

	i = 0;
	while (i < 5 && (*format)[i])
		i++;
	if (i == 5 && (color = ptf_search_color(*format)) != -1)
	{
		ptf_print_color(color);
		*format += 5;
	}
	return (1);
}
